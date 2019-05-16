#1

SELECT g.name, count(s.id), sum(a.duration) as sumdur, round(avg(a.duration),0) as avgdur
FROM AD18___DB.groups g 
    left outer join AD18___DB.shares s on g.ID = s.group_id
    left outer join AD18___DB.audio a on a.ID = s.audio_id
group by g.name
;

#2

SELECT name1 as name, S_count, sumdur, avgdur, M_count
FROM
    (SELECT g.name as name1, count(s.id) as S_count, sum(a.duration) as sumdur, round(avg(a.duration),0) as avgdur
    FROM AD18___DB.shares s 
        RIGHT OUTER JOIN AD18___DB.groups g ON g.id = s.group_id
        LEFT OUTER JOIN AD18___DB.audio a ON a.id = s.audio_id
    GROUP BY g.name)
    LEFT OUTER JOIN 
    (SELECT g.name as name2, count(m.user_id) as M_count
    FROM AD18___DB.groups g
        LEFT OUTER JOIN AD18___DB.members m ON g.user_id = m.user_id
    GROUP BY g.name) 
    ON name1 = name2
;

#3

SELECT to_char(u.created_at, 'yyyy-mm') as reg_ym, count(u.id) as reg_count
FROM AD18___DB.users u
GROUP BY to_char(u.created_at, 'yyyy-mm')
;

