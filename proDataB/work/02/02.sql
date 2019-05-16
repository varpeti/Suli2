#4

SELECT to_char(h.started_at, 'YYYY-MM-DD HH24:MI:SS'), h.duration, to_char(h.started_at+h.duration/24/60/60, 'YYYY-MM-DD HH24:MI:SS')
FROM AD18___DB.historyitems h
;

#5

SELECT
    h.id,
    h.user_id,
    to_char(h.started_at, 'YYYY-MM-DD HH24:MI:SS') AS sta, 
    h.duration AS dur, 
    to_char(h.started_at+h.duration/24/60/60, 'YYYY-MM-DD HH24:MI:SS') AS fin,
    (h.started_at)
        - (LAG(h.started_at+h.duration/24/60/60) OVER (PARTITION BY user_id ORDER BY h.started_at)) AS dif
FROM AD18___DB.historyitems h
ORDER BY user_id, h.started_at
;

#6

SELECT *
FROM 
(
    SELECT 
        TO_CHAR(h.started_at, 'YYYY-MM') as "dat", 
        a.title as "title",
        sum(h.duration) as "dur",
        count(h.audio_id) as "cx",
        DENSE_RANK() OVER (PARTITION BY TO_CHAR(h.started_at, 'YYYY-MM') ORDER BY count(h.audio_id) DESC, sum(h.duration) ) as "rank"
    FROM AD18___DB.historyitems h
        INNER JOIN AD18___DB.audio a ON a.id = h.audio_id
    GROUP BY 
        TO_CHAR(h.started_at, 'YYYY-MM'), 
        a.title
)
WHERE "rank"<4
ORDER BY 
    "dat",
    "rank",
    "dur" DESC
;