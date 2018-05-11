LAYERS = "Default Mask"

function generate(layers)
    c = Color(0)
    c.r = 1

    for x=layers:startX(), layers:endX()-1, 1 do
        for y=layers:startY(), layers:endY()-1, 1 do
            layers:set(0, x, y, c)
        end
    end
end
