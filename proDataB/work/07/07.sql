SELECT 'alma';

SELECT ST_SetSRID(ST_Point(47.501947, 19.034393),4326);


SELECT ST_asKML(ST_SetSRID(ST_Point(47.501947, 19.034393),4326));


SELECT ST_asKML
(
    ST_Transform
    (
        ST_Buffer
        (  
            ST_Transform
            ( 
                ST_SetSRID(ST_Point(19.034393, 47.501947),4326),
                23700
            ),
            2500
        ),
        4326
    )
);

SELECT hu_2po_4pgr.osm_name
FROM hu_2po_4pgr
WHERE ST_Intersects
(
    hu_2po_4pgr.geom_way,
    ST_Transform
    (
        ST_Buffer
        (  
            ST_Transform
            ( 
                ST_SetSRID(ST_Point(19.034393, 47.501947),4326),
                23700
            ),
            2500
        ),
        4326
    )
)
;