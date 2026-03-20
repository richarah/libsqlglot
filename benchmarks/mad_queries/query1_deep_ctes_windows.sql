-- TRULY MAD: 15 levels of nested CTEs with window functions stacked on window functions
WITH
  l1 AS (
    SELECT user_id, score, region, country, premium, active, created_at,
           ROW_NUMBER() OVER (PARTITION BY region ORDER BY score DESC) AS rn1,
           RANK() OVER (PARTITION BY country ORDER BY score DESC) AS rank1,
           DENSE_RANK() OVER (ORDER BY score DESC) AS drank1,
           LAG(score, 1, 0) OVER (PARTITION BY region ORDER BY user_id) AS lag1,
           LEAD(score, 1, 0) OVER (PARTITION BY region ORDER BY user_id) AS lead1,
           SUM(score) OVER (PARTITION BY region ORDER BY user_id ROWS BETWEEN 5 PRECEDING AND 5 FOLLOWING) AS sum1,
           AVG(score) OVER (PARTITION BY country ORDER BY user_id ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS avg1,
           MIN(score) OVER (PARTITION BY premium ORDER BY score) AS min1,
           MAX(score) OVER (PARTITION BY active ORDER BY score) AS max1,
           COUNT(*) OVER (PARTITION BY region, country ORDER BY score) AS cnt1
    FROM users WHERE active = 1
  ),
  l2 AS (
    SELECT *,
           ROW_NUMBER() OVER (PARTITION BY rank1 ORDER BY rn1) AS rn2,
           RANK() OVER (PARTITION BY drank1 ORDER BY sum1 DESC) AS rank2,
           DENSE_RANK() OVER (ORDER BY avg1 DESC) AS drank2,
           LAG(sum1, 2, 0) OVER (PARTITION BY region ORDER BY rn1) AS lag2,
           LEAD(avg1, 3, 0) OVER (PARTITION BY country ORDER BY rn1) AS lead2,
           SUM(sum1) OVER (PARTITION BY region ORDER BY rn1 ROWS BETWEEN 10 PRECEDING AND 10 FOLLOWING) AS sum2,
           AVG(avg1) OVER (PARTITION BY country ORDER BY rn1 ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS avg2,
           MIN(min1) OVER (PARTITION BY premium ORDER BY sum1) AS min2,
           MAX(max1) OVER (PARTITION BY active ORDER BY avg1) AS max2,
           COUNT(*) OVER (PARTITION BY region, premium ORDER BY sum1) AS cnt2
    FROM l1 WHERE rn1 <= 1000
  ),
  l3 AS (
    SELECT *,
           ROW_NUMBER() OVER (PARTITION BY rank2 ORDER BY rn2, rn1) AS rn3,
           RANK() OVER (PARTITION BY drank2 ORDER BY sum2 DESC, avg2 DESC) AS rank3,
           DENSE_RANK() OVER (ORDER BY avg2 DESC, sum2 DESC) AS drank3,
           LAG(sum2, 1, 0) OVER (PARTITION BY region ORDER BY rn2) AS lag3,
           LEAD(avg2, 1, 0) OVER (PARTITION BY country ORDER BY rn2) AS lead3,
           SUM(sum2) OVER (PARTITION BY region ORDER BY rn2 ROWS BETWEEN 15 PRECEDING AND 15 FOLLOWING) AS sum3,
           AVG(avg2) OVER (PARTITION BY country ORDER BY rn2 ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS avg3,
           MIN(min2) OVER (PARTITION BY premium ORDER BY sum2) AS min3,
           MAX(max2) OVER (PARTITION BY active ORDER BY avg2) AS max3,
           COUNT(*) OVER (PARTITION BY region, country, premium ORDER BY sum2) AS cnt3
    FROM l2 WHERE rank2 <= 500
  ),
  l4 AS (
    SELECT *,
           ROW_NUMBER() OVER (PARTITION BY rank3 ORDER BY rn3, rn2, rn1) AS rn4,
           RANK() OVER (PARTITION BY drank3 ORDER BY sum3 DESC, avg3 DESC, sum2 DESC) AS rank4,
           DENSE_RANK() OVER (ORDER BY avg3 DESC, sum3 DESC, avg2 DESC) AS drank4,
           LAG(sum3, 2, 0) OVER (PARTITION BY region ORDER BY rn3) AS lag4,
           LEAD(avg3, 2, 0) OVER (PARTITION BY country ORDER BY rn3) AS lead4,
           SUM(sum3) OVER (PARTITION BY region ORDER BY rn3 ROWS BETWEEN 20 PRECEDING AND 20 FOLLOWING) AS sum4,
           AVG(avg3) OVER (PARTITION BY country ORDER BY rn3 ROWS BETWEEN UNBOUNDED PRECEDING AND CURRENT ROW) AS avg4
    FROM l3 WHERE drank3 <= 250
  ),
  l5 AS (
    SELECT *,
           ROW_NUMBER() OVER (PARTITION BY rank4 ORDER BY rn4, rn3) AS rn5,
           RANK() OVER (PARTITION BY drank4 ORDER BY sum4 DESC, avg4 DESC) AS rank5,
           DENSE_RANK() OVER (ORDER BY avg4 DESC, sum4 DESC) AS drank5,
           LAG(sum4, 3, 0) OVER (PARTITION BY region ORDER BY rn4) AS lag5,
           LEAD(avg4, 3, 0) OVER (PARTITION BY country ORDER BY rn4) AS lead5,
           SUM(sum4) OVER (PARTITION BY region ORDER BY rn4) AS sum5,
           AVG(avg4) OVER (PARTITION BY country ORDER BY rn4) AS avg5
    FROM l4 WHERE rank4 <= 100
  ),
  l6 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum5 DESC, avg5 DESC, sum4 DESC) AS rn6,
           RANK() OVER (PARTITION BY drank5 ORDER BY sum5 DESC) AS rank6,
           LAG(sum5, 1, 0) OVER (ORDER BY rn5) AS lag6,
           LEAD(avg5, 1, 0) OVER (ORDER BY rn5) AS lead6,
           SUM(sum5) OVER (ORDER BY rn5 ROWS BETWEEN 25 PRECEDING AND 25 FOLLOWING) AS sum6,
           AVG(avg5) OVER (ORDER BY rn5) AS avg6
    FROM l5 WHERE rank5 <= 50
  ),
  l7 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum6 DESC, avg6 DESC) AS rn7,
           RANK() OVER (ORDER BY sum6 DESC) AS rank7,
           LAG(sum6, 2, 0) OVER (ORDER BY rn6) AS lag7,
           LEAD(avg6, 2, 0) OVER (ORDER BY rn6) AS lead7,
           SUM(sum6) OVER (ORDER BY rn6) AS sum7,
           AVG(avg6) OVER (ORDER BY rn6) AS avg7
    FROM l6 WHERE rn6 <= 25
  ),
  l8 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum7 DESC) AS rn8,
           RANK() OVER (ORDER BY avg7 DESC) AS rank8,
           LAG(sum7, 1, 0) OVER (ORDER BY rn7) AS lag8,
           LEAD(avg7, 1, 0) OVER (ORDER BY rn7) AS lead8,
           SUM(sum7) OVER (ORDER BY rn7) AS sum8,
           AVG(avg7) OVER (ORDER BY rn7) AS avg8
    FROM l7 WHERE rank7 <= 20
  ),
  l9 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum8 DESC) AS rn9,
           LAG(sum8, 1, 0) OVER (ORDER BY rn8) AS lag9,
           LEAD(avg8, 1, 0) OVER (ORDER BY rn8) AS lead9,
           SUM(sum8) OVER (ORDER BY rn8) AS sum9,
           AVG(avg8) OVER (ORDER BY rn8) AS avg9
    FROM l8 WHERE rn8 <= 15
  ),
  l10 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum9 DESC) AS rn10,
           SUM(sum9) OVER (ORDER BY rn9) AS sum10,
           AVG(avg9) OVER (ORDER BY rn9) AS avg10
    FROM l9 WHERE rn9 <= 10
  ),
  l11 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum10 DESC) AS rn11,
           SUM(sum10) OVER (ORDER BY rn10) AS sum11,
           AVG(avg10) OVER (ORDER BY rn10) AS avg11
    FROM l10
  ),
  l12 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum11 DESC) AS rn12,
           SUM(sum11) OVER (ORDER BY rn11) AS sum12
    FROM l11
  ),
  l13 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum12 DESC) AS rn13,
           SUM(sum12) OVER (ORDER BY rn12) AS sum13
    FROM l12
  ),
  l14 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum13 DESC) AS rn14,
           SUM(sum13) OVER (ORDER BY rn13) AS sum14
    FROM l13
  ),
  l15 AS (
    SELECT *,
           ROW_NUMBER() OVER (ORDER BY sum14 DESC) AS final_rank
    FROM l14
  )
SELECT user_id, score, region, country, final_rank, sum14, sum13, sum12, sum11, sum10
FROM l15
ORDER BY final_rank
