SELECT DISTINCT C.customer_name, C.customer_city 
FROM    banking.customer C join banking.borrower B on C.customer_name = B.customer_name 
        join banking.loan L on B.loan_number = L.loan_number 
WHERE   branch_name LIKE 'Perryridge'; 

SELECT DISTINCT *
FROM banking.customer;

SELECT DISTINCT *
FROM banking.borrower;

SELECT DISTINCT *
FROM banking.loan;

CREATE VIEW T1 AS
    SELECT DISTINCT C.customer_name, C.customer_city, L.loan_number, L.branch_name
    FROM banking.customer C join banking.borrower B on C.customer_name = B.customer_name 
         join banking.loan L on B.loan_number = L.loan_number
;

CREATE VIEW T2 AS
    SELECT DISTINCT L.branch_name
    FROM banking.borrower B join banking.loan L on B.loan_number = L.loan_number
    WHERE B.customer_name like 'Williams'
;

SELECT DISTINCT T1.customer_name, T1.customer_city
FROM T1
WHERE T1.branch_name in (SELECT T2.branch_name FROM T2)
GROUP BY T1.customer_name, T1.customer_city
HAVING count(*) = (SELECT count(*) FROM T2)
;

DROP VIEW T2;
DROP VIEW T1;

SELECT DISTINCT * 
FROM
(
    SELECT DISTINCT customer_city, count(customer_name) as num
    FROM banking.customer
    GROUP BY customer_city
)
WHERE num = any(2,4)
;

SELECT DISTINCT customer_city, count(customer_name) as num
FROM banking.customer
GROUP BY customer_city
HAVING customer_city like '%oo%'
;