-- TRULY MAD: 20-way joins with window functions everywhere
SELECT
  u.user_id,
  u.name,
  u.email,
  o.order_id,
  o.total,
  o.status,
  oi.order_item_id,
  oi.quantity,
  oi.price,
  p.product_id,
  p.product_name,
  p.price AS product_price,
  c.category_id,
  c.category_name,
  s.supplier_id,
  s.supplier_name,
  w.warehouse_id,
  w.warehouse_name,
  sh.shipment_id,
  sh.shipped_date,
  sh.delivered_date,
  r.review_id,
  r.rating,
  r.comment,
  pm.payment_id,
  pm.payment_method,
  pm.amount,
  addr.address_id,
  addr.city,
  addr.country,
  ROW_NUMBER() OVER (PARTITION BY u.user_id ORDER BY o.created_at DESC) AS user_order_rank,
  ROW_NUMBER() OVER (PARTITION BY p.product_id ORDER BY o.created_at DESC) AS product_order_rank,
  ROW_NUMBER() OVER (PARTITION BY c.category_id ORDER BY o.total DESC) AS category_order_rank,
  RANK() OVER (PARTITION BY u.region ORDER BY o.total DESC) AS region_order_rank,
  DENSE_RANK() OVER (ORDER BY o.total DESC) AS global_order_rank,
  LAG(o.total, 1, 0) OVER (PARTITION BY u.user_id ORDER BY o.created_at) AS prev_order_total,
  LAG(o.total, 2, 0) OVER (PARTITION BY u.user_id ORDER BY o.created_at) AS prev_prev_order_total,
  LAG(o.total, 3, 0) OVER (PARTITION BY u.user_id ORDER BY o.created_at) AS prev_prev_prev_order_total,
  LEAD(o.total, 1, 0) OVER (PARTITION BY u.user_id ORDER BY o.created_at) AS next_order_total,
  LEAD(o.total, 2, 0) OVER (PARTITION BY u.user_id ORDER BY o.created_at) AS next_next_order_total,
  LEAD(o.total, 3, 0) OVER (PARTITION BY u.user_id ORDER BY o.created_at) AS next_next_next_order_total,
  SUM(o.total) OVER (PARTITION BY u.user_id ORDER BY o.created_at ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS running_user_total,
  SUM(o.total) OVER (PARTITION BY c.category_id ORDER BY o.created_at ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS running_category_total,
  SUM(o.total) OVER (PARTITION BY u.region ORDER BY o.created_at ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS running_region_total,
  AVG(o.total) OVER (PARTITION BY u.user_id ORDER BY o.created_at ROWS BETWEEN 10 PRECEDING AND CURRENT ROW) AS user_rolling_avg_10,
  AVG(o.total) OVER (PARTITION BY u.user_id ORDER BY o.created_at ROWS BETWEEN 20 PRECEDING AND CURRENT ROW) AS user_rolling_avg_20,
  AVG(o.total) OVER (PARTITION BY u.user_id ORDER BY o.created_at ROWS BETWEEN 50 PRECEDING AND CURRENT ROW) AS user_rolling_avg_50,
  AVG(o.total) OVER (PARTITION BY c.category_id ORDER BY o.created_at ROWS BETWEEN 100 PRECEDING AND CURRENT ROW) AS category_rolling_avg,
  AVG(o.total) OVER (PARTITION BY u.region ORDER BY o.created_at ROWS BETWEEN 100 PRECEDING AND CURRENT ROW) AS region_rolling_avg,
  MIN(o.total) OVER (PARTITION BY u.user_id ORDER BY o.created_at ROWS BETWEEN 10 PRECEDING AND CURRENT ROW) AS user_rolling_min,
  MAX(o.total) OVER (PARTITION BY u.user_id ORDER BY o.created_at ROWS BETWEEN 10 PRECEDING AND CURRENT ROW) AS user_rolling_max,
  MIN(o.total) OVER (PARTITION BY c.category_id) AS category_min_order,
  MAX(o.total) OVER (PARTITION BY c.category_id) AS category_max_order,
  COUNT(*) OVER (PARTITION BY u.user_id ORDER BY o.created_at ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS cumulative_user_orders,
  COUNT(*) OVER (PARTITION BY p.product_id ORDER BY o.created_at ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS cumulative_product_orders,
  COUNT(*) OVER (PARTITION BY c.category_id ORDER BY o.created_at ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS cumulative_category_orders,
  SUM(oi.quantity) OVER (PARTITION BY u.user_id ORDER BY o.created_at) AS cumulative_user_quantity,
  SUM(oi.quantity) OVER (PARTITION BY p.product_id ORDER BY o.created_at) AS cumulative_product_quantity,
  AVG(r.rating) OVER (PARTITION BY u.user_id ORDER BY r.created_at ROWS BETWEEN 5 PRECEDING AND CURRENT ROW) AS user_rolling_rating_avg,
  AVG(r.rating) OVER (PARTITION BY p.product_id ORDER BY r.created_at ROWS BETWEEN 10 PRECEDING AND CURRENT ROW) AS product_rolling_rating_avg,
  SUM(pm.amount) OVER (PARTITION BY u.user_id ORDER BY pm.payment_date ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS cumulative_payments
FROM users u
INNER JOIN orders o ON u.user_id = o.user_id
INNER JOIN order_items oi ON o.order_id = oi.order_id
INNER JOIN products p ON oi.product_id = p.product_id
INNER JOIN categories c ON p.category_id = c.category_id
INNER JOIN suppliers s ON p.supplier_id = s.supplier_id
LEFT JOIN inventory i ON p.product_id = i.product_id
LEFT JOIN warehouses w ON i.warehouse_id = w.warehouse_id
LEFT JOIN shipments sh ON o.order_id = sh.order_id
LEFT JOIN reviews r ON o.order_id = r.order_id AND u.user_id = r.user_id
LEFT JOIN payments pm ON o.order_id = pm.order_id
LEFT JOIN addresses addr ON u.user_id = addr.user_id AND addr.address_type = 'shipping'
LEFT JOIN (
  SELECT user_id, COUNT(*) AS referral_count
  FROM referrals
  GROUP BY user_id
) ref ON u.user_id = ref.user_id
LEFT JOIN (
  SELECT user_id, COUNT(*) AS wishlist_count
  FROM wishlist_items
  GROUP BY user_id
) wl ON u.user_id = wl.user_id
LEFT JOIN (
  SELECT user_id, COUNT(*) AS cart_count
  FROM cart_items
  GROUP BY user_id
) cart ON u.user_id = cart.user_id
LEFT JOIN (
  SELECT user_id, MAX(login_date) AS last_login
  FROM logins
  GROUP BY user_id
) logins ON u.user_id = logins.user_id
LEFT JOIN (
  SELECT user_id, COUNT(DISTINCT friend_id) AS friend_count
  FROM friends
  GROUP BY user_id
) friends ON u.user_id = friends.user_id
LEFT JOIN (
  SELECT user_id, COUNT(*) AS subscription_count, SUM(price) AS subscription_revenue
  FROM subscriptions
  WHERE status = 'active'
  GROUP BY user_id
) subs ON u.user_id = subs.user_id
LEFT JOIN (
  SELECT user_id, SUM(points) AS loyalty_points
  FROM loyalty_transactions
  GROUP BY user_id
) loyalty ON u.user_id = loyalty.user_id
LEFT JOIN (
  SELECT user_id, COUNT(*) AS coupon_count
  FROM coupon_usage
  GROUP BY user_id
) coupons ON u.user_id = coupons.user_id
WHERE
  u.active = 1
  AND o.status IN ('completed', 'shipped', 'delivered')
  AND o.created_at >= '2024-01-01'
  AND p.discontinued = 0
  AND (r.rating IS NULL OR r.rating >= 3)
ORDER BY
  u.user_id,
  o.created_at DESC,
  oi.order_item_id
