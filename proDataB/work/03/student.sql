DROP TABLE student;
DROP SEQUENCE student_seq;
DROP TRIGGER student_bri;
CREATE TABLE student
(
  name       VARCHAR(20) NOT NULL,
  sex        VARCHAR(2) NOT NULL,
  student_id NUMBER NOT NULL,
  PRIMARY KEY (student_id)
);

CREATE SEQUENCE student_seq
START WITH 1
INCREMENT BY 1;

CREATE OR REPLACE TRIGGER student_bri
BEFORE INSERT
ON student
REFERENCING NEW AS NEW
FOR EACH ROW
BEGIN
SELECT student_seq.nextval INTO :NEW.student_id FROM dual;
END;
/

INSERT INTO student VALUES ('Megan','F',NULL);
INSERT INTO student VALUES ('Joseph','M',NULL);
INSERT INTO student VALUES ('Kyle','M',NULL);
INSERT INTO student VALUES ('Katie','F',NULL);
INSERT INTO student VALUES ('Abby','F',NULL);
INSERT INTO student VALUES ('Nathan','M',NULL);
INSERT INTO student VALUES ('Liesl','F',NULL);
INSERT INTO student VALUES ('Ian','M',NULL);
INSERT INTO student VALUES ('Colin','M',NULL);
INSERT INTO student VALUES ('Peter','M',NULL);
INSERT INTO student VALUES ('Michael','M',NULL);
INSERT INTO student VALUES ('Thomas','M',NULL);
INSERT INTO student VALUES ('Devri','F',NULL);
INSERT INTO student VALUES ('Ben','M',NULL);
INSERT INTO student VALUES ('Aubrey','F',NULL);
INSERT INTO student VALUES ('Rebecca','F',NULL);
INSERT INTO student VALUES ('Will','M',NULL);
INSERT INTO student VALUES ('Max','M',NULL);
INSERT INTO student VALUES ('Rianne','F',NULL);
INSERT INTO student VALUES ('Avery','F',NULL);
INSERT INTO student VALUES ('Lauren','F',NULL);
INSERT INTO student VALUES ('Becca','F',NULL);
INSERT INTO student VALUES ('Gregory','M',NULL);
INSERT INTO student VALUES ('Sarah','F',NULL);
INSERT INTO student VALUES ('Robbie','M',NULL);
INSERT INTO student VALUES ('Keaton','M',NULL);
INSERT INTO student VALUES ('Carter','M',NULL);
INSERT INTO student VALUES ('Teddy','M',NULL);
INSERT INTO student VALUES ('Gabrielle','F',NULL);
INSERT INTO student VALUES ('Grace','F',NULL);
INSERT INTO student VALUES ('Emily','F',NULL);


COMMIT;