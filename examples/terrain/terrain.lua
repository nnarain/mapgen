LAYERS = "Land Elevation Moisture Temperature Biomes Final"

LAND        = 0
ELEVATION   = 1
MOISTURE    = 2
TEMPERATURE = 3
BIOMES      = 4
FINAL       = 5


Tundra           = 0
BorealForest     = 1
BorealBarren     = 2
TemperatelForest = 3
Savanna          = 4
GrassLand        = 5
Desert           = 6
Rainforest       = 7

function generate(layers, params)
    landMaskNoise = params:getNoise("land_mask")
    elevationNoise = params:getNoise("elevation")
    moistureNoise = params:getNoise("moisture")
    temperatureNoise = params:getNoise("temperature")

    seaLevel = params:getFloat("sea_level")

    landDark = params:getColor("land_dark")
    landLight = params:getColor("land_light")
    waterLight = params:getColor("water_light")
    waterDark = params:getColor("water_dark")
    cold = params:getColor("cold")
    hot = params:getColor("hot")

    t1 = params:getFloat("t1")
    t2 = params:getFloat("t2")
    t3 = params:getFloat("t3")

    m1 = params:getFloat("m1")
    m2 = params:getFloat("m2")
    m3 = params:getFloat("m3")

    for x=layers:startX(), layers:endX()-1, 1 do
        for y=layers:startY(), layers:endY()-1, 1 do
            landMask = landMaskNoise:sample(x, y)

            cl = nil
            ce = nil
            cm = nil
            ct = nil
            cb = nil
            cf = nil

            if landMask > seaLevel then
                cl = Color.from(landDark, landLight, landMask)

                elevation = utils.range(elevationNoise:sample(x, y), -1, 1, 0, 1)
                ce = Color.from(Color(0), Color(1), elevation)

                moisture = utils.range(moistureNoise:sample(x, y), -1, 1, 0, 1)
                cm = Color.from(waterLight, waterDark, moisture)

                temperature = utils.range(temperatureNoise:sample(x, y), -1, 1, 0, 1) * 2.0
                ct = Color.from(cold, hot, temperature / 2.0)

                biome = getBiome(temperature, moisture, t1, t2, t3, m1, m2, m3)
                cb = biomeToColor(biome, params)

                cf = Color.from(cb, landDark, elevation)
            else
                cl = Color.from(waterLight, waterDark, 1.0 - landMask)
                ce = Color(1)
                cm = Color(1)
                ct = Color(1)
                cb = Color(1)

                cf = cl
            end

            layers:set(LAND, x, y, cl)
            layers:set(ELEVATION, x, y, ce)
            layers:set(MOISTURE, x, y, cm)
            layers:set(TEMPERATURE, x, y, ct)
            layers:set(BIOMES, x, y, cb)
            layers:set(FINAL, x, y, cf)
        end
    end
end

function getBiome(t, m, t1, t2, t3, m1, m2, m3)
    if t >= t1 then
        if m >= m1 then
            return Rainforest
        elseif m >= m2 then
            return TemperatelForest
        elseif m >= m3 then
            return GrassLand
        else
            return Desert
        end
    elseif t >= t2 then
        if m >= m1 then
            return TemperatelForest
        elseif m >= m2 then
            return GrassLand
        elseif m >= m3 then
            return GrassLand
        else
            return Desert
        end
    elseif t >= t3 then
        if m >= m2 then
            return BorealForest
        else
            return BorealBarren
        end
    else
        return Tundra
    end
end

function biomeToColor(biome, params)
    if biome == Rainforest then
        return params:getColor("rainforest")
    elseif biome == TemperatelForest then
        return params:getColor("temperate")
    elseif biome == GrassLand then
        return params:getColor("grassland")
    elseif biome == Desert then
        return params:getColor("desert")
    elseif biome == BorealForest then
        return params:getColor("boreal")
    elseif biome == BorealBarren then
        return params:getColor("boreal_barren")
    else
        return params:getColor("tundra")
    end
end
