SELECT ROWID
FROM student
;

SELECT s.name
FROM student s
WHERE s.name like 'B%'
;

CREATE INDEX student_name_ix ON student (name);

DROP INDEX student_name_ix;

#

SELECT name, sex
FROM student
;

CREATE INDEX student_name_ix ON student (name);

SELECT name, sex
FROM student
WHERE SEX='F'
;

SELECT *
FROM student
WHERE SEX='F'
;

DROP INDEX student_name_ix;

#

SELECT /*+ NO_INDEX(HISTORYITEMS_LARGE) */ *
FROM AD18___DB.historyitems_large
WHERE id<10
;

SELECT *
FROM AD18___DB.historyitems_large
WHERE id<10
;

SELECT *
FROM AD18___DB.historyitems_large
WHERE 
    to_date('2014.01', 'YYYY.MM') < started_at
    and to_date('2015.03', 'YYYY.MM') > started_at
;

SELECT *
FROM AD18___DB.historyitems_large
WHERE 
    to_date('2014.01', 'YYYY.MM') < started_at
    and to_date('2015.03', 'YYYY.MM') > started_at
    and ROWNUM < 100
;