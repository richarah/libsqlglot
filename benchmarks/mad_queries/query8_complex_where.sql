-- TRULY MAD: WHERE clause with 100+ conditions - a Boolean nightmare
SELECT
  user_id,
  name,
  email,
  score,
  region,
  country,
  active,
  premium,
  created_at
FROM users
WHERE
  (
    (active = 1 AND score >= 1000 AND premium = 1)
    OR
    (active = 1 AND score >= 2000 AND premium = 0)
    OR
    (active = 0 AND score >= 5000 AND premium = 1 AND created_at >= '2024-01-01')
  )
  AND
  (
    (region = 'NA' AND country IN ('US', 'CA', 'MX') AND score >= 500)
    OR
    (region = 'NA' AND country = 'US' AND score >= 300)
    OR
    (region = 'NA' AND country = 'CA' AND score >= 400)
    OR
    (region = 'EU' AND country IN ('UK', 'DE', 'FR', 'IT', 'ES', 'NL', 'BE', 'CH', 'AT', 'SE') AND score >= 600)
    OR
    (region = 'EU' AND country IN ('PL', 'CZ', 'HU', 'RO') AND score >= 400)
    OR
    (region = 'APAC' AND country IN ('JP', 'CN', 'IN', 'AU', 'SG', 'KR') AND score >= 700)
    OR
    (region = 'APAC' AND country IN ('TH', 'VN', 'ID', 'PH') AND score >= 500)
    OR
    (region NOT IN ('NA', 'EU', 'APAC') AND score >= 300)
  )
  AND
  (
    (premium = 1 AND created_at >= '2023-01-01' AND score >= 1000)
    OR
    (premium = 1 AND created_at >= '2022-01-01' AND score >= 2000)
    OR
    (premium = 0 AND created_at >= '2024-01-01' AND score >= 500)
    OR
    (premium = 0 AND created_at >= '2023-01-01' AND score >= 1500)
  )
  AND
  (
    (email LIKE '%@gmail.com' AND score >= 400)
    OR
    (email LIKE '%@yahoo.com' AND score >= 450)
    OR
    (email LIKE '%@hotmail.com' AND score >= 500)
    OR
    (email LIKE '%@outlook.com' AND score >= 500)
    OR
    (email LIKE '%@protonmail.com' AND score >= 600)
    OR
    (email LIKE '%@icloud.com' AND score >= 550)
    OR
    (email NOT LIKE '%@gmail.com' AND email NOT LIKE '%@yahoo.com' AND email NOT LIKE '%@hotmail.com' AND score >= 300)
  )
  AND
  (
    score BETWEEN 100 AND 20000
    OR
    (score < 100 AND created_at >= '2024-09-01')
    OR
    (score > 20000 AND premium = 1)
  )
  AND
  (
    (user_id % 2 = 0 AND region = 'NA')
    OR
    (user_id % 3 = 0 AND region = 'EU')
    OR
    (user_id % 5 = 0 AND region = 'APAC')
    OR
    (user_id % 7 = 0 AND premium = 1)
    OR
    (user_id % 11 = 0)
  )
  AND NOT (
    (country = 'XX' AND region = 'YY')
    OR
    (score = 0 AND active = 1 AND created_at < '2020-01-01')
    OR
    (premium = 1 AND created_at < '2019-01-01' AND score < 100)
    OR
    (email LIKE '%test%' OR email LIKE '%fake%' OR email LIKE '%spam%')
  )
  AND
  (
    (LENGTH(name) >= 5 AND LENGTH(name) <= 50)
    OR
    (LENGTH(name) > 50 AND premium = 1)
    OR
    (LENGTH(name) < 5 AND created_at >= '2024-01-01')
  )
  AND
  (
    (LENGTH(email) BETWEEN 10 AND 100)
    OR
    (LENGTH(email) > 100 AND premium = 1)
  )
  AND
  (
    (region = 'NA' AND score >= 200 AND active = 1)
    OR
    (region = 'NA' AND score >= 500 AND active = 0 AND premium = 1)
    OR
    (region = 'EU' AND score >= 300 AND active = 1)
    OR
    (region = 'EU' AND score >= 600 AND active = 0 AND premium = 1)
    OR
    (region = 'APAC' AND score >= 400 AND active = 1)
    OR
    (region = 'APAC' AND score >= 700 AND active = 0 AND premium = 1)
    OR
    (region NOT IN ('NA', 'EU', 'APAC') AND score >= 150)
  )
  AND
  (
    (country IN ('US', 'CA', 'UK', 'DE', 'FR', 'JP', 'AU') AND score >= 400)
    OR
    (country IN ('MX', 'IT', 'ES', 'CN', 'IN', 'BR') AND score >= 500)
    OR
    (country IN ('NL', 'BE', 'CH', 'AT', 'SE', 'NO', 'DK', 'FI') AND score >= 450)
    OR
    (country IN ('PL', 'CZ', 'HU', 'RO', 'BG', 'HR', 'SI') AND score >= 350)
    OR
    (country IN ('KR', 'SG', 'HK', 'TW') AND score >= 600)
    OR
    (country IN ('TH', 'VN', 'ID', 'PH', 'MY') AND score >= 400)
    OR
    (country NOT IN ('US', 'CA', 'UK', 'DE', 'FR', 'JP', 'AU', 'MX', 'IT', 'ES', 'CN', 'IN', 'BR', 'NL', 'BE', 'CH', 'AT', 'SE', 'NO', 'DK', 'FI', 'PL', 'CZ', 'HU', 'RO', 'BG', 'HR', 'SI', 'KR', 'SG', 'HK', 'TW', 'TH', 'VN', 'ID', 'PH', 'MY') AND score >= 250)
  )
  AND
  (
    (created_at >= '2024-01-01' AND created_at < '2024-04-01' AND score >= 300)
    OR
    (created_at >= '2024-04-01' AND created_at < '2024-07-01' AND score >= 350)
    OR
    (created_at >= '2024-07-01' AND created_at < '2024-10-01' AND score >= 400)
    OR
    (created_at >= '2024-10-01' AND score >= 450)
    OR
    (created_at >= '2023-01-01' AND created_at < '2024-01-01' AND score >= 600)
    OR
    (created_at >= '2022-01-01' AND created_at < '2023-01-01' AND score >= 800)
    OR
    (created_at < '2022-01-01' AND score >= 1200)
  )
  AND
  (
    (premium = 1 AND active = 1 AND score >= 500)
    OR
    (premium = 1 AND active = 0 AND score >= 1500)
    OR
    (premium = 0 AND active = 1 AND score >= 300)
    OR
    (premium = 0 AND active = 0 AND score >= 2000 AND created_at >= '2023-01-01')
  )
  AND
  (
    (score >= 10000 AND region IN ('NA', 'EU'))
    OR
    (score >= 8000 AND score < 10000 AND region IN ('NA', 'EU', 'APAC'))
    OR
    (score >= 5000 AND score < 8000)
    OR
    (score >= 2000 AND score < 5000 AND active = 1)
    OR
    (score >= 1000 AND score < 2000 AND active = 1 AND premium = 1)
    OR
    (score >= 500 AND score < 1000 AND created_at >= '2024-01-01')
    OR
    (score >= 100 AND score < 500 AND created_at >= '2024-06-01')
    OR
    (score < 100 AND created_at >= '2024-09-01' AND active = 1)
  )
ORDER BY
  CASE
    WHEN premium = 1 AND active = 1 THEN 1
    WHEN premium = 1 AND active = 0 THEN 2
    WHEN premium = 0 AND active = 1 THEN 3
    WHEN premium = 0 AND active = 0 THEN 4
    ELSE 5
  END,
  CASE
    WHEN region = 'NA' THEN 1
    WHEN region = 'EU' THEN 2
    WHEN region = 'APAC' THEN 3
    ELSE 4
  END,
  score DESC,
  created_at DESC,
  user_id
