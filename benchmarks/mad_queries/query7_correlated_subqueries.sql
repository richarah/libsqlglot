-- TRULY MAD: Every column is a deeply nested correlated subquery
SELECT
  u.user_id,
  u.name,
  (SELECT COUNT(*) FROM orders WHERE user_id = u.user_id) AS order_count,
  (SELECT COUNT(*) FROM orders WHERE user_id = u.user_id AND total > (SELECT AVG(total) FROM orders WHERE user_id = u.user_id)) AS above_avg_orders,
  (SELECT COUNT(*) FROM orders WHERE user_id = u.user_id AND total > (SELECT AVG(total) * 1.5 FROM orders WHERE user_id = u.user_id)) AS well_above_avg_orders,
  (SELECT COUNT(*) FROM orders WHERE user_id = u.user_id AND total > (SELECT AVG(total) * 2 FROM orders WHERE user_id = u.user_id)) AS double_avg_orders,
  (SELECT SUM(total) FROM orders WHERE user_id = u.user_id AND created_at >= (SELECT MIN(created_at) FROM orders WHERE user_id = u.user_id AND EXTRACT(YEAR FROM created_at) = 2024)) AS total_2024,
  (SELECT COUNT(DISTINCT product_id) FROM order_items oi INNER JOIN orders o ON oi.order_id = o.order_id WHERE o.user_id = u.user_id AND oi.product_id IN (SELECT product_id FROM products WHERE category_id IN (SELECT category_id FROM categories WHERE name LIKE '%Electronics%'))) AS electronics_products,
  (SELECT COUNT(*) FROM reviews r WHERE r.user_id = u.user_id AND r.rating >= (SELECT AVG(rating) FROM reviews WHERE product_id = r.product_id)) AS above_avg_reviews,
  (SELECT COUNT(*) FROM reviews r WHERE r.user_id = u.user_id AND r.rating < (SELECT AVG(rating) FROM reviews WHERE product_id = r.product_id)) AS below_avg_reviews,
  (SELECT MAX(total) FROM orders o WHERE o.user_id = u.user_id AND o.created_at = (SELECT MAX(created_at) FROM orders WHERE user_id = u.user_id)) AS latest_order_amount,
  (SELECT COUNT(*) FROM orders o WHERE o.user_id = u.user_id AND o.total = (SELECT MAX(total) FROM orders WHERE user_id = u.user_id)) AS max_order_count,
  (SELECT AVG(total) FROM orders o WHERE o.user_id = u.user_id AND EXTRACT(MONTH FROM o.created_at) = (SELECT EXTRACT(MONTH FROM MAX(created_at)) FROM orders WHERE user_id = u.user_id)) AS current_month_avg,
  (SELECT COUNT(*) FROM logins l WHERE l.user_id = u.user_id AND l.login_date >= (SELECT DATE(MAX(login_date), '-30 days') FROM logins WHERE user_id = u.user_id)) AS logins_last_30_days,
  (SELECT COUNT(DISTINCT friend_id) FROM friends f WHERE f.user_id = u.user_id AND f.friend_id IN (SELECT user_id FROM users WHERE score > (SELECT AVG(score) FROM users))) AS high_score_friends,
  (SELECT SUM(total) FROM orders o WHERE o.user_id = u.user_id AND o.order_id IN (SELECT order_id FROM order_items oi WHERE oi.product_id IN (SELECT product_id FROM products p WHERE p.supplier_id IN (SELECT supplier_id FROM suppliers WHERE country = (SELECT country FROM users WHERE user_id = u.user_id))))) AS domestic_supplier_revenue
FROM users u
WHERE
  u.active = 1
  AND EXISTS (
    SELECT 1 FROM orders o
    WHERE o.user_id = u.user_id
    AND o.total > (
      SELECT AVG(total) FROM orders
      WHERE user_id = u.user_id
      AND status IN (
        SELECT DISTINCT status FROM orders
        WHERE user_id = u.user_id
        AND created_at >= (
          SELECT MIN(created_at) FROM orders
          WHERE user_id = u.user_id
          AND EXTRACT(YEAR FROM created_at) = EXTRACT(YEAR FROM CURRENT_DATE)
        )
      )
    )
  )
  AND u.score > (
    SELECT AVG(score) FROM users u2
    WHERE u2.region = u.region
    AND u2.user_id IN (
      SELECT user_id FROM orders
      WHERE total > (
        SELECT AVG(total) FROM orders o3
        WHERE o3.user_id = u2.user_id
      )
      GROUP BY user_id
      HAVING COUNT(*) > (
        SELECT AVG(order_count) FROM (
          SELECT user_id, COUNT(*) AS order_count
          FROM orders
          GROUP BY user_id
        ) avg_orders
      )
    )
  )
  AND NOT EXISTS (
    SELECT 1 FROM orders o
    WHERE o.user_id = u.user_id
    AND o.order_id IN (
      SELECT order_id FROM order_items oi
      WHERE oi.product_id IN (
        SELECT product_id FROM products
        WHERE discontinued = 1
        AND category_id IN (
          SELECT category_id FROM categories
          WHERE deprecated = 1
          AND category_id NOT IN (
            SELECT DISTINCT category_id
            FROM products p2
            INNER JOIN order_items oi2 ON p2.product_id = oi2.product_id
            INNER JOIN orders o2 ON oi2.order_id = o2.order_id
            WHERE o2.user_id = u.user_id
            AND o2.status = 'completed'
            AND o2.created_at >= (
              SELECT DATE(MAX(created_at), '-365 days')
              FROM orders
              WHERE user_id = u.user_id
            )
          )
        )
      )
    )
  )
ORDER BY
  (SELECT COUNT(*) FROM orders WHERE user_id = u.user_id) DESC,
  (SELECT SUM(total) FROM orders WHERE user_id = u.user_id) DESC,
  u.score DESC
