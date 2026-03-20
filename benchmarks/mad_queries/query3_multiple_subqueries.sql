-- TRULY MAD: Subquery hell - subqueries within subqueries within subqueries, correlated everywhere
SELECT
  u.user_id,
  u.name,
  u.score,
  (SELECT COUNT(*) FROM orders o WHERE o.user_id = u.user_id) AS total_orders,
  (SELECT COUNT(*) FROM orders o WHERE o.user_id = u.user_id AND o.status = 'completed') AS completed_orders,
  (SELECT COUNT(*) FROM orders o WHERE o.user_id = u.user_id AND o.status = 'pending') AS pending_orders,
  (SELECT COUNT(*) FROM orders o WHERE o.user_id = u.user_id AND o.status = 'cancelled') AS cancelled_orders,
  (SELECT SUM(total) FROM orders o WHERE o.user_id = u.user_id AND o.status = 'completed') AS total_revenue,
  (SELECT AVG(total) FROM orders o WHERE o.user_id = u.user_id AND o.status = 'completed') AS avg_order_value,
  (SELECT MAX(total) FROM orders o WHERE o.user_id = u.user_id) AS max_order,
  (SELECT MIN(total) FROM orders o WHERE o.user_id = u.user_id AND o.total > 0) AS min_order,
  (SELECT COUNT(*) FROM orders o WHERE o.user_id = u.user_id AND o.total > (SELECT AVG(total) FROM orders WHERE user_id = u.user_id)) AS above_avg_orders,
  (SELECT COUNT(*) FROM orders o WHERE o.user_id = u.user_id AND o.total < (SELECT AVG(total) FROM orders WHERE user_id = u.user_id)) AS below_avg_orders,
  (SELECT MAX(created_at) FROM orders o WHERE o.user_id = u.user_id) AS last_order_date,
  (SELECT MIN(created_at) FROM orders o WHERE o.user_id = u.user_id) AS first_order_date,
  (SELECT COUNT(DISTINCT product_id) FROM order_items oi INNER JOIN orders o ON oi.order_id = o.order_id WHERE o.user_id = u.user_id) AS unique_products,
  (SELECT COUNT(DISTINCT category_id) FROM order_items oi INNER JOIN orders o ON oi.order_id = o.order_id INNER JOIN products p ON oi.product_id = p.product_id WHERE o.user_id = u.user_id) AS unique_categories,
  (SELECT AVG(rating) FROM reviews r WHERE r.user_id = u.user_id) AS avg_rating,
  (SELECT COUNT(*) FROM reviews r WHERE r.user_id = u.user_id AND r.rating >= 4) AS positive_reviews,
  (SELECT COUNT(*) FROM reviews r WHERE r.user_id = u.user_id AND r.rating <= 2) AS negative_reviews,
  (SELECT COUNT(DISTINCT friend_id) FROM friends f WHERE f.user_id = u.user_id) AS friend_count,
  (SELECT COUNT(*) FROM logins l WHERE l.user_id = u.user_id) AS login_count,
  (SELECT MAX(login_date) FROM logins l WHERE l.user_id = u.user_id) AS last_login,
  (SELECT COUNT(*) FROM subscriptions s WHERE s.user_id = u.user_id AND s.status = 'active') AS active_subscriptions
FROM
  (
    SELECT *
    FROM
      (
        SELECT *
        FROM
          (
            SELECT *
            FROM
              (
                SELECT *
                FROM
                  (
                    SELECT
                      u.user_id,
                      u.name,
                      u.email,
                      u.score,
                      u.region,
                      u.country,
                      u.active,
                      u.premium,
                      (SELECT COUNT(*) FROM orders WHERE user_id = u.user_id) AS order_count
                    FROM users u
                    WHERE u.active = 1
                  ) AS level1
                WHERE level1.order_count > (SELECT AVG(order_count) FROM (SELECT user_id, COUNT(*) AS order_count FROM orders GROUP BY user_id) AS avg_orders)
              ) AS level2
            WHERE level2.score > (SELECT AVG(score) FROM users WHERE region = level2.region)
          ) AS level3
        WHERE level3.user_id NOT IN (SELECT user_id FROM banned_users WHERE banned_at > '2023-01-01')
      ) AS level4
    WHERE level4.user_id IN (
      SELECT user_id
      FROM orders
      WHERE total > (
        SELECT AVG(total) * 1.5
        FROM orders
        WHERE user_id = level4.user_id
      )
    )
  ) AS u
WHERE
  u.score > (SELECT AVG(score) FROM users WHERE active = 1)
  AND u.user_id IN (
    SELECT o.user_id
    FROM orders o
    WHERE o.total > (
      SELECT AVG(total)
      FROM orders
      WHERE user_id = o.user_id
    )
    AND o.created_at > (
      SELECT MIN(created_at)
      FROM orders
      WHERE user_id = o.user_id
      AND status = 'completed'
    )
  )
  AND u.user_id NOT IN (
    SELECT b.user_id
    FROM banned_users b
    WHERE b.banned_at > (
      SELECT MIN(created_at)
      FROM orders
      WHERE user_id = b.user_id
    )
  )
  AND EXISTS (
    SELECT 1
    FROM orders o
    WHERE o.user_id = u.user_id
    AND o.total > (
      SELECT AVG(total) * 2
      FROM orders
      WHERE user_id = u.user_id
      AND status = 'completed'
    )
  )
  AND EXISTS (
    SELECT 1
    FROM subscriptions s
    WHERE s.user_id = u.user_id
    AND s.status = 'active'
    AND s.plan_id IN (
      SELECT p.plan_id
      FROM plans p
      WHERE p.price > (
        SELECT AVG(price)
        FROM plans
        WHERE category = p.category
      )
    )
  )
  AND NOT EXISTS (
    SELECT 1
    FROM order_items oi
    INNER JOIN orders o ON oi.order_id = o.order_id
    WHERE o.user_id = u.user_id
    AND oi.product_id IN (
      SELECT product_id
      FROM products
      WHERE discontinued = 1
      AND category_id IN (
        SELECT category_id
        FROM categories
        WHERE deprecated = 1
      )
    )
  )
  AND u.score > (
    SELECT CASE
      WHEN u.region = 'NA' THEN (SELECT AVG(score) * 1.2 FROM users WHERE region = 'NA' AND active = 1)
      WHEN u.region = 'EU' THEN (SELECT AVG(score) * 1.3 FROM users WHERE region = 'EU' AND active = 1)
      WHEN u.region = 'APAC' THEN (SELECT AVG(score) * 1.4 FROM users WHERE region = 'APAC' AND active = 1)
      ELSE (SELECT AVG(score) FROM users WHERE active = 1)
    END
  )
ORDER BY
  (SELECT COUNT(*) FROM orders WHERE user_id = u.user_id AND status = 'completed') DESC,
  (SELECT SUM(total) FROM orders WHERE user_id = u.user_id AND status = 'completed') DESC,
  u.score DESC
