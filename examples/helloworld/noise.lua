LAYERS = "Default Mask"

function generate(layers, params)
    noise = params:getNoise("mynoise")

    for x=layers:startX(), layers:endX()-1, 1 do
        for y=layers:startY(), layers:endY()-1, 1 do
            sample = noise:sample(x, y)
            c = Color(sample)

            layers:set(0, x, y, c)
        end
    end
end
