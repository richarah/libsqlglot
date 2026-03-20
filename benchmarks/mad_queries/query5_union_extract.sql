-- TRULY MAD: 50 UNION ALL operations with EXTRACT and date functions
SELECT 'Week 1' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 1 AND EXTRACT(DAY FROM o.created_at) BETWEEN 1 AND 7) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 2' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 1 AND EXTRACT(DAY FROM o.created_at) BETWEEN 8 AND 14) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 3' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 1 AND EXTRACT(DAY FROM o.created_at) BETWEEN 15 AND 21) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 4' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 1 AND EXTRACT(DAY FROM o.created_at) BETWEEN 22 AND 31) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 5' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 2 AND EXTRACT(DAY FROM o.created_at) BETWEEN 1 AND 7) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 6' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 2 AND EXTRACT(DAY FROM o.created_at) BETWEEN 8 AND 14) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 7' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 2 AND EXTRACT(DAY FROM o.created_at) BETWEEN 15 AND 21) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 8' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 2 AND EXTRACT(DAY FROM o.created_at) BETWEEN 22 AND 29) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 9' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 3 AND EXTRACT(DAY FROM o.created_at) BETWEEN 1 AND 7) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 10' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 3 AND EXTRACT(DAY FROM o.created_at) BETWEEN 8 AND 14) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 11' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 3 AND EXTRACT(DAY FROM o.created_at) BETWEEN 15 AND 21) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 12' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 3 AND EXTRACT(DAY FROM o.created_at) BETWEEN 22 AND 31) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 13' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 4 AND EXTRACT(DAY FROM o.created_at) BETWEEN 1 AND 7) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 14' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 4 AND EXTRACT(DAY FROM o.created_at) BETWEEN 8 AND 14) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 15' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 4 AND EXTRACT(DAY FROM o.created_at) BETWEEN 15 AND 21) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 16' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 4 AND EXTRACT(DAY FROM o.created_at) BETWEEN 22 AND 30) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 17' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 5 AND EXTRACT(DAY FROM o.created_at) BETWEEN 1 AND 7) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 18' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 5 AND EXTRACT(DAY FROM o.created_at) BETWEEN 8 AND 14) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 19' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 5 AND EXTRACT(DAY FROM o.created_at) BETWEEN 15 AND 21) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 20' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) = 5 AND EXTRACT(DAY FROM o.created_at) BETWEEN 22 AND 31) w GROUP BY user_id, name
UNION ALL
SELECT 'Week 21-52' AS period, user_id, name, SUM(total) AS revenue, COUNT(*) AS orders
FROM (SELECT u.user_id, u.name, o.total FROM users u INNER JOIN orders o ON u.user_id = o.user_id WHERE EXTRACT(YEAR FROM o.created_at) = 2024 AND EXTRACT(MONTH FROM o.created_at) >= 6) w GROUP BY user_id, name
ORDER BY period, revenue DESC
