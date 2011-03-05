require 'RMagick'
require 'sdl'

require 'options.rb'
require 'search.rb'
require 'agent.rb'
require 'agents.rb'
require 'graphics.rb'

# Convert a SDL pixel to an array of three RGB values. Each value goes from 0-255.
def rgbFromPixel(pixel)
	return Graphics::instance.screen.getRGB(Graphics::instance.screen.mapRGB(pixel.red, pixel.green, pixel.blue))
end

# Computes the total distance between two pixels.
# Right now it just adds up the difference of each RGB value.
# It might be smarter to figure out the real 3D distance between the two values using the pythagorean theorem.
def rgbDistance(rgb1, rgb2)
	distance = 0
	3.times do |i|
		distance += ((rgb1[i] - rgb2[i]).abs) ** 2
	end

	return Math.sqrt(distance)
end

Search::instance.loadImages(HAYSTACK_PATH, NEEDLE_PATH)

NUM_AGENTS.times do |i|
	new_agent = Agent.new(0, 0, Search::instance.needle.columns, Search::instance.needle.rows).randomize()
	new_agent.update_state
	Agents::instance.add(new_agent)
end

running = true
frame = 0
while running
	Graphics::instance.screen.fill_rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, Graphics::instance.screen.mapRGB(0, 0, 0))

	while event = SDL::Event2.poll
		case event
		when SDL::Event2::Quit
			running = false
		end
	end

	Search::instance.draw()
	
	Agents::instance.draw()

	Graphics::instance.screen.flip

	# update
	if frame != 0 and frame % UPDATE_FRAME == 0
		# update the state of each agent first
		Agents::instance.each { |a| a.update_state }

		# now have each agent either move or stay in the same place depending on its state
		Agents::instance.each { |a| a.update }
	end

	frame += 1
end
