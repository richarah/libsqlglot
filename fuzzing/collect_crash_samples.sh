#!/bin/bash
# Extract crash-inducing inputs from fuzzer debug logs

echo "Collecting crash samples from fuzzer logs..."

# Create crash samples directory
mkdir -p crash_samples

# Extract problematic queries from debug logs
# These are the queries that were being parsed when crashes occurred

cat > crash_samples/sample_01.sql << 'EOF'
SELECT IN (SELECT y FROM  IN (SELECT y FROM s) s)  * FROM (SELECT * FROM t) s
EOF

cat > crash_samples/sample_02.sql << 'EOF'
SELECT x FROM t WHERE  EXISTS (SELECT 1 FROM t WHERE x = y) x = x
EOF

cat > crash_samples/sample_03.sql << 'EOF'
SELECT DISTINCT x FROM t UNION SELECT DISTINCT x FROM t AND T x     F
EOF

cat > crash_samples/sample_04.sql << 'EOF'
SELECT * FROM t W DENSE_RANK HERE 1=1 AND ANK HERE 1=1
EOF

cat > crash_samples/sample_05.sql << 'EOF'
SELECT * FROM t    WHERE    x  EXISTS (SELECT 1 FROM t WHERE x = y) IN (SELECT
EOF

cat > crash_samples/sample_06.sql << 'EOF'
SELECT COUNT(*) FROM (SELECT D DENSE_RANK ISTINCT x FROM t) s
EOF

cat > crash_samples/sample_07.sql << 'EOF'
SELECT x, y FROM (SELECT x FROM (SELECT * FROM t) s)  t WHERE x > 0 AND x > 0 AN
EOF

cat > crash_samples/sample_08.sql << 'EOF'
SELECT * FROM t JOIN t t2 O WHEN N t.id = t2.id AND FROM t JOIN t t2 ON t.i
EOF

cat > crash_samples/sample_09.sql << 'EOF'
SELECT SUM(x), SUM(x) FROM t AND SUM(x) FROM
EOF

cat > crash_samples/sample_10.sql << 'EOF'
SEL (SELECT x FROM (SELECT * FROM t) s) ECT * FROM t WHERE EXIST IN (SELECT y FR
EOF

echo "Created $(ls crash_samples/*.sql | wc -l) crash samples"
ls -1 crash_samples/
