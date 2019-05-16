SELECT COUNT(*)
FROM AD18___DB.audio_large
INNER JOIN AD18___DB.historyitems_large
ON audio_large.id = historyitems_large.audio_id;

SELECT COUNT(historyitems_large.rating)
FROM AD18___DB.audio_large
INNER JOIN AD18___DB.historyitems_large
ON audio_large.id = historyitems_large.audio_id;

SELECT AVG(historyitems_large.rating)
FROM AD18___DB.audio_large
INNER JOIN AD18___DB.historyitems_large
ON audio_large.id = historyitems_large.audio_id;

SELECT COUNT(historyitems_large.updated_at)
FROM AD18___DB.audio_large
INNER JOIN AD18___DB.historyitems_large
ON audio_large.id = historyitems_large.audio_id;


SELECT COUNT(audio_large.user_id)
FROM AD18___DB.audio_large INNER JOIN AD18___DB.historyitems_large
ON audio_large.id = historyitems_large.audio_id;

SELECT COUNT(audio_large.user_id)
FROM AD18___DB.audio_large
INNER JOIN AD18___DB.historyitems_large
ON audio_large.id BETWEEN historyitems_large.audio_id - 0.5 AND
historyitems_large.audio_id + 0.5 ;

SELECT COUNT(audio_large.user_id)
FROM AD18___DB.audio_large
INNER JOIN AD18___DB.historyitems_large
ON audio_large.id - historyitems_large.audio_id = 0;