-- TRULY MAD: CASE expressions nested 35 levels deep - a monstrosity
SELECT
  user_id,
  name,
  CASE
    WHEN score >= 10000 THEN
      CASE
        WHEN region = 'NA' THEN
          CASE
            WHEN premium = 1 THEN
              CASE
                WHEN age < 18 THEN
                  CASE WHEN country = 'US' THEN 'US-Teen-Elite-Premium' WHEN country = 'CA' THEN 'CA-Teen-Elite-Premium' ELSE 'NA-Teen-Elite-Premium' END
                WHEN age >= 18 AND age < 30 THEN
                  CASE WHEN country = 'US' THEN 'US-Young-Elite-Premium' WHEN country = 'CA' THEN 'CA-Young-Elite-Premium' ELSE 'NA-Young-Elite-Premium' END
                WHEN age >= 30 AND age < 50 THEN
                  CASE WHEN country = 'US' THEN 'US-Adult-Elite-Premium' WHEN country = 'CA' THEN 'CA-Adult-Elite-Premium' ELSE 'NA-Adult-Elite-Premium' END
                ELSE
                  CASE WHEN country = 'US' THEN 'US-Senior-Elite-Premium' WHEN country = 'CA' THEN 'CA-Senior-Elite-Premium' ELSE 'NA-Senior-Elite-Premium' END
              END
            ELSE
              CASE
                WHEN age < 18 THEN
                  CASE WHEN active = 1 THEN 'NA-Teen-Elite-Active' ELSE 'NA-Teen-Elite-Inactive' END
                WHEN age >= 18 AND age < 30 THEN
                  CASE WHEN active = 1 THEN 'NA-Young-Elite-Active' ELSE 'NA-Young-Elite-Inactive' END
                ELSE
                  CASE WHEN active = 1 THEN 'NA-Adult-Elite-Active' ELSE 'NA-Adult-Elite-Inactive' END
              END
          END
        WHEN region = 'EU' THEN
          CASE
            WHEN premium = 1 THEN
              CASE
                WHEN country = 'UK' THEN
                  CASE WHEN age < 25 THEN 'UK-Young-Elite-Premium' WHEN age >= 25 AND age < 45 THEN 'UK-Mid-Elite-Premium' ELSE 'UK-Senior-Elite-Premium' END
                WHEN country = 'DE' THEN
                  CASE WHEN age < 25 THEN 'DE-Young-Elite-Premium' WHEN age >= 25 AND age < 45 THEN 'DE-Mid-Elite-Premium' ELSE 'DE-Senior-Elite-Premium' END
                WHEN country = 'FR' THEN
                  CASE WHEN age < 25 THEN 'FR-Young-Elite-Premium' WHEN age >= 25 AND age < 45 THEN 'FR-Mid-Elite-Premium' ELSE 'FR-Senior-Elite-Premium' END
                ELSE
                  CASE WHEN age < 25 THEN 'EU-Young-Elite-Premium' WHEN age >= 25 AND age < 45 THEN 'EU-Mid-Elite-Premium' ELSE 'EU-Senior-Elite-Premium' END
              END
            ELSE
              CASE
                WHEN active = 1 THEN
                  CASE WHEN age < 30 THEN 'EU-Young-Elite-Free-Active' ELSE 'EU-Adult-Elite-Free-Active' END
                ELSE
                  CASE WHEN age < 30 THEN 'EU-Young-Elite-Free-Inactive' ELSE 'EU-Adult-Elite-Free-Inactive' END
              END
          END
        WHEN region = 'APAC' THEN
          CASE
            WHEN premium = 1 THEN
              CASE
                WHEN country = 'JP' THEN
                  CASE WHEN age < 20 THEN 'JP-Teen-Elite' WHEN age >= 20 AND age < 40 THEN 'JP-Adult-Elite' ELSE 'JP-Senior-Elite' END
                WHEN country = 'CN' THEN
                  CASE WHEN age < 20 THEN 'CN-Teen-Elite' WHEN age >= 20 AND age < 40 THEN 'CN-Adult-Elite' ELSE 'CN-Senior-Elite' END
                WHEN country = 'IN' THEN
                  CASE WHEN age < 20 THEN 'IN-Teen-Elite' WHEN age >= 20 AND age < 40 THEN 'IN-Adult-Elite' ELSE 'IN-Senior-Elite' END
                ELSE
                  CASE WHEN age < 20 THEN 'APAC-Teen-Elite' WHEN age >= 20 AND age < 40 THEN 'APAC-Adult-Elite' ELSE 'APAC-Senior-Elite' END
              END
            ELSE
              CASE WHEN active = 1 THEN 'APAC-Elite-Free-Active' ELSE 'APAC-Elite-Free-Inactive' END
          END
        ELSE
          CASE WHEN premium = 1 THEN 'Other-Elite-Premium' ELSE 'Other-Elite-Free' END
      END
    WHEN score >= 5000 THEN
      CASE
        WHEN region = 'NA' THEN
          CASE
            WHEN premium = 1 THEN
              CASE
                WHEN age < 25 THEN
                  CASE WHEN score >= 7500 THEN 'NA-Young-High-Premium' ELSE 'NA-Young-Mid-Premium' END
                ELSE
                  CASE WHEN score >= 7500 THEN 'NA-Adult-High-Premium' ELSE 'NA-Adult-Mid-Premium' END
              END
            ELSE
              CASE
                WHEN active = 1 THEN
                  CASE WHEN score >= 7500 THEN 'NA-High-Active' ELSE 'NA-Mid-Active' END
                ELSE
                  CASE WHEN score >= 7500 THEN 'NA-High-Inactive' ELSE 'NA-Mid-Inactive' END
              END
          END
        WHEN region = 'EU' THEN
          CASE
            WHEN premium = 1 THEN
              CASE
                WHEN country IN ('UK', 'DE', 'FR') THEN
                  CASE WHEN age < 30 THEN 'EU-Major-Young-High' ELSE 'EU-Major-Adult-High' END
                ELSE
                  CASE WHEN age < 30 THEN 'EU-Minor-Young-High' ELSE 'EU-Minor-Adult-High' END
              END
            ELSE
              CASE WHEN active = 1 THEN 'EU-High-Active' ELSE 'EU-High-Inactive' END
          END
        ELSE
          CASE
            WHEN premium = 1 THEN
              CASE WHEN score >= 7500 THEN 'Other-VHigh-Premium' ELSE 'Other-High-Premium' END
            ELSE
              CASE WHEN score >= 7500 THEN 'Other-VHigh-Free' ELSE 'Other-High-Free' END
          END
      END
    WHEN score >= 2500 THEN
      CASE
        WHEN premium = 1 THEN
          CASE
            WHEN region = 'NA' THEN
              CASE
                WHEN active = 1 THEN
                  CASE WHEN age < 35 THEN 'NA-Premium-MidHigh-Young-Active' ELSE 'NA-Premium-MidHigh-Senior-Active' END
                ELSE
                  CASE WHEN age < 35 THEN 'NA-Premium-MidHigh-Young-Inactive' ELSE 'NA-Premium-MidHigh-Senior-Inactive' END
              END
            WHEN region = 'EU' THEN
              CASE
                WHEN active = 1 THEN
                  CASE WHEN age < 35 THEN 'EU-Premium-MidHigh-Young-Active' ELSE 'EU-Premium-MidHigh-Senior-Active' END
                ELSE
                  CASE WHEN age < 35 THEN 'EU-Premium-MidHigh-Young-Inactive' ELSE 'EU-Premium-MidHigh-Senior-Inactive' END
              END
            ELSE
              CASE WHEN active = 1 THEN 'Other-Premium-MidHigh-Active' ELSE 'Other-Premium-MidHigh-Inactive' END
          END
        ELSE
          CASE
            WHEN active = 1 THEN
              CASE
                WHEN age < 25 THEN
                  CASE WHEN score >= 3500 THEN 'Free-MidHigh-Young-VActive' ELSE 'Free-MidHigh-Young-Active' END
                ELSE
                  CASE WHEN score >= 3500 THEN 'Free-MidHigh-Adult-VActive' ELSE 'Free-MidHigh-Adult-Active' END
              END
            ELSE
              CASE WHEN score >= 3500 THEN 'Free-MidHigh-Inactive-Upper' ELSE 'Free-MidHigh-Inactive-Lower' END
          END
      END
    WHEN score >= 1000 THEN
      CASE
        WHEN region = 'NA' THEN
          CASE
            WHEN premium = 1 THEN
              CASE WHEN active = 1 THEN 'NA-Mid-Premium-Active' ELSE 'NA-Mid-Premium-Inactive' END
            ELSE
              CASE
                WHEN active = 1 THEN
                  CASE WHEN age < 30 THEN 'NA-Mid-Free-Young-Active' ELSE 'NA-Mid-Free-Adult-Active' END
                ELSE
                  CASE WHEN age < 30 THEN 'NA-Mid-Free-Young-Inactive' ELSE 'NA-Mid-Free-Adult-Inactive' END
              END
          END
        WHEN region = 'EU' THEN
          CASE
            WHEN premium = 1 THEN
              CASE WHEN active = 1 THEN 'EU-Mid-Premium-Active' ELSE 'EU-Mid-Premium-Inactive' END
            ELSE
              CASE WHEN active = 1 THEN 'EU-Mid-Free-Active' ELSE 'EU-Mid-Free-Inactive' END
          END
        ELSE
          CASE
            WHEN premium = 1 THEN 'Other-Mid-Premium'
            ELSE
              CASE WHEN active = 1 THEN 'Other-Mid-Free-Active' ELSE 'Other-Mid-Free-Inactive' END
          END
      END
    WHEN score >= 500 THEN
      CASE
        WHEN premium = 1 THEN
          CASE
            WHEN active = 1 THEN
              CASE WHEN age < 25 THEN 'LowMid-Premium-Young-Active' ELSE 'LowMid-Premium-Adult-Active' END
            ELSE
              CASE WHEN age < 25 THEN 'LowMid-Premium-Young-Inactive' ELSE 'LowMid-Premium-Adult-Inactive' END
          END
        ELSE
          CASE
            WHEN active = 1 THEN
              CASE
                WHEN region IN ('NA', 'EU') THEN
                  CASE WHEN score >= 750 THEN 'West-LowMid-Upper-Active' ELSE 'West-LowMid-Lower-Active' END
                ELSE
                  CASE WHEN score >= 750 THEN 'East-LowMid-Upper-Active' ELSE 'East-LowMid-Lower-Active' END
              END
            ELSE
              CASE WHEN score >= 750 THEN 'LowMid-Upper-Inactive' ELSE 'LowMid-Lower-Inactive' END
          END
      END
    WHEN score >= 100 THEN
      CASE
        WHEN active = 1 THEN
          CASE
            WHEN premium = 1 THEN
              CASE WHEN created_at >= '2024-01-01' THEN 'Low-Premium-Active-Recent' ELSE 'Low-Premium-Active-Old' END
            ELSE
              CASE
                WHEN created_at >= '2024-01-01' THEN
                  CASE WHEN score >= 300 THEN 'Low-Free-Active-Recent-Upper' ELSE 'Low-Free-Active-Recent-Lower' END
                ELSE
                  CASE WHEN score >= 300 THEN 'Low-Free-Active-Old-Upper' ELSE 'Low-Free-Active-Old-Lower' END
              END
          END
        ELSE
          CASE
            WHEN created_at >= '2024-01-01' THEN
              CASE WHEN premium = 1 THEN 'Low-Inactive-Recent-Premium' ELSE 'Low-Inactive-Recent-Free' END
            ELSE
              CASE WHEN premium = 1 THEN 'Low-Inactive-Old-Premium' ELSE 'Low-Inactive-Old-Free' END
          END
      END
    ELSE
      CASE
        WHEN created_at >= '2024-06-01' THEN
          CASE
            WHEN active = 1 THEN
              CASE WHEN premium = 1 THEN 'Beginner-VeryRecent-Active-Premium' ELSE 'Beginner-VeryRecent-Active-Free' END
            ELSE
              CASE WHEN premium = 1 THEN 'Beginner-VeryRecent-Inactive-Premium' ELSE 'Beginner-VeryRecent-Inactive-Free' END
          END
        WHEN created_at >= '2024-01-01' THEN
          CASE
            WHEN active = 1 THEN
              CASE WHEN region IN ('NA', 'EU') THEN 'Beginner-Recent-Active-West' ELSE 'Beginner-Recent-Active-East' END
            ELSE
              CASE WHEN region IN ('NA', 'EU') THEN 'Beginner-Recent-Inactive-West' ELSE 'Beginner-Recent-Inactive-East' END
          END
        ELSE
          CASE
            WHEN active = 1 THEN
              CASE
                WHEN premium = 1 THEN 'Beginner-Old-Active-Premium'
                ELSE
                  CASE WHEN score >= 50 THEN 'Beginner-Old-Active-Free-Upper' ELSE 'Beginner-Old-Active-Free-Lower' END
              END
            ELSE
              CASE
                WHEN premium = 1 THEN 'Beginner-Old-Inactive-Premium'
                ELSE
                  CASE WHEN score >= 50 THEN 'Beginner-Old-Inactive-Free-Upper' ELSE 'Beginner-Old-Inactive-Free-Lower' END
              END
          END
      END
  END AS insanely_nested_category,
  score * CASE WHEN score > 9000 THEN 2.5 WHEN score > 7000 THEN 2.0 WHEN score > 5000 THEN 1.8 WHEN score > 3000 THEN 1.5 WHEN score > 1000 THEN 1.3 WHEN score > 500 THEN 1.1 ELSE 1.0 END AS weighted_score
FROM users
WHERE active = 1 OR premium = 1
