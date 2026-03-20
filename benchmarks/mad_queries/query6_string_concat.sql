-- TRULY MAD: String manipulation nightmare - 20+ levels of nested string functions
SELECT
  user_id,
  UPPER(LOWER(UPPER(LOWER(UPPER(LOWER(UPPER(LOWER(UPPER(LOWER(name)))))))))) AS pointless_name,
  CONCAT(
    SUBSTR(CONCAT(UPPER(SUBSTR(first_name, 1, 1)), LOWER(SUBSTR(first_name, 2))), 1, 20),
    ' ',
    SUBSTR(CONCAT(UPPER(SUBSTR(last_name, 1, 1)), LOWER(SUBSTR(last_name, 2))), 1, 20),
    ' (',
    REPLACE(REPLACE(REPLACE(REPLACE(REPLACE(
      email,
      '@gmail.com', '@g'),
      '@yahoo.com', '@y'),
      '@hotmail.com', '@h'),
      '@outlook.com', '@o'),
      '@protonmail.com', '@p'),
    ')'
  ) AS name_with_email,
  CONCAT(
    CASE
      WHEN SUBSTR(email, 1, 1) BETWEEN 'a' AND 'e' THEN UPPER(SUBSTR(email, 1, 3))
      WHEN SUBSTR(email, 1, 1) BETWEEN 'f' AND 'j' THEN LOWER(SUBSTR(email, 1, 3))
      WHEN SUBSTR(email, 1, 1) BETWEEN 'k' AND 'o' THEN UPPER(SUBSTR(email, 1, 3))
      WHEN SUBSTR(email, 1, 1) BETWEEN 'p' AND 't' THEN LOWER(SUBSTR(email, 1, 3))
      ELSE UPPER(SUBSTR(email, 1, 3))
    END,
    '-',
    CAST(LENGTH(email) AS VARCHAR),
    '-',
    CAST(LENGTH(REPLACE(email, 'a', '')) AS VARCHAR),
    '-',
    CAST(LENGTH(REPLACE(email, 'e', '')) AS VARCHAR),
    '-',
    CAST(LENGTH(REPLACE(email, 'i', '')) AS VARCHAR),
    '-',
    CAST(LENGTH(REPLACE(email, 'o', '')) AS VARCHAR),
    '-',
    CAST(LENGTH(REPLACE(email, 'u', '')) AS VARCHAR)
  ) AS email_analysis,
  CONCAT(
    SUBSTR(CONCAT(
      SUBSTR(CONCAT(region, '-', country, '-', city), 1, 10),
      '-',
      SUBSTR(CONCAT(postal_code, '-', address_line1), 1, 15)
    ), 1, 25),
    '...',
    SUBSTR(CONCAT(
      REVERSE(SUBSTR(REVERSE(region), 1, 3)),
      REVERSE(SUBSTR(REVERSE(country), 1, 3)),
      REVERSE(SUBSTR(REVERSE(city), 1, 3))
    ), 1, 9)
  ) AS location_hash,
  REPLACE(
    REPLACE(
      REPLACE(
        REPLACE(
          REPLACE(
            REPLACE(
              REPLACE(
                REPLACE(
                  REPLACE(
                    REPLACE(phone_number, '0', 'X'),
                  '1', 'X'),
                '2', 'X'),
              '3', 'X'),
            '4', 'X'),
          '5', 'X'),
        '6', 'X'),
      '7', 'X'),
    '8', 'X'),
  '9', 'X') AS masked_phone,
  CONCAT(
    'User: ',
    CAST(user_id AS VARCHAR),
    ' | Name: ',
    CONCAT(
      SUBSTR(UPPER(first_name), 1, 1),
      REPEAT('*', GREATEST(LENGTH(first_name) - 2, 0)),
      CASE WHEN LENGTH(first_name) > 1 THEN SUBSTR(first_name, LENGTH(first_name), 1) ELSE '' END
    ),
    ' ',
    CONCAT(
      SUBSTR(UPPER(last_name), 1, 1),
      REPEAT('*', GREATEST(LENGTH(last_name) - 2, 0)),
      CASE WHEN LENGTH(last_name) > 1 THEN SUBSTR(last_name, LENGTH(last_name), 1) ELSE '' END
    ),
    ' | Email: ',
    CONCAT(
      SUBSTR(email, 1, 2),
      REPEAT('*', GREATEST(INSTR(email, '@') - 3, 0)),
      SUBSTR(email, INSTR(email, '@') - 1)
    ),
    ' | Score: ',
    CAST(score AS VARCHAR),
    ' (',
    CASE
      WHEN score >= 10000 THEN 'ELITE'
      WHEN score >= 5000 THEN 'ADVANCED'
      WHEN score >= 1000 THEN 'INTERMEDIATE'
      ELSE 'BEGINNER'
    END,
    ')',
    ' | Status: ',
    CASE WHEN active = 1 THEN 'ACTIVE' ELSE 'INACTIVE' END,
    CASE WHEN premium = 1 THEN ' [PREMIUM]' ELSE '' END,
    ' | Joined: ',
    SUBSTR(CAST(created_at AS VARCHAR), 1, 10),
    ' (',
    CASE
      WHEN created_at >= '2024-01-01' THEN 'RECENT'
      WHEN created_at >= '2023-01-01' THEN '2023'
      WHEN created_at >= '2022-01-01' THEN '2022'
      ELSE 'OLD'
    END,
    ')'
  ) AS full_user_summary,
  CONCAT(
    REVERSE(SUBSTR(REVERSE(UPPER(CONCAT(first_name, last_name))), 1, 3)),
    '-',
    CAST((user_id % 1000) AS VARCHAR),
    '-',
    SUBSTR(MD5(email), 1, 6),
    '-',
    CASE
      WHEN region = 'NA' THEN 'N'
      WHEN region = 'EU' THEN 'E'
      WHEN region = 'APAC' THEN 'A'
      ELSE 'O'
    END,
    CASE
      WHEN premium = 1 THEN 'P'
      ELSE 'F'
    END,
    CASE
      WHEN active = 1 THEN 'A'
      ELSE 'I'
    END
  ) AS user_code
FROM (
  SELECT
    user_id,
    name,
    email,
    region,
    country,
    city,
    postal_code,
    address_line1,
    phone_number,
    score,
    active,
    premium,
    created_at,
    SUBSTR(name, 1, CASE WHEN INSTR(name, ' ') > 0 THEN INSTR(name, ' ') - 1 ELSE LENGTH(name) END) AS first_name,
    CASE
      WHEN INSTR(name, ' ') > 0 THEN SUBSTR(name, INSTR(name, ' ') + 1)
      ELSE name
    END AS last_name
  FROM users
  WHERE LENGTH(name) > 0 AND LENGTH(email) > 5
) parsed_users
ORDER BY user_id
