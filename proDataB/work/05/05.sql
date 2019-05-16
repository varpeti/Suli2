SET SERVEROUTPUT ON; 

CREATE OR REPLACE PROCEDURE exist_table (table_name_in IN VARCHAR2 ) IS
    table_name VARCHAR2(30);
BEGIN
    table_name := UPPER(table_name_in);
    DBMS_OUTPUT.put_line('Hello ' || table_name || '!');
    
END;