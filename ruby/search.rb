class Search
	attr_accessor :needle, :haystack, :max_distance

	def loadImages(needle, haystack)
		@needle = Magick::Image.read(needle).first
		@haystack = Magick::Image.read(haystack).first

		# compute the maximum distance an agent could be from the right solution. This is used in calculating the distance percentage.
		# note to self -- this only works because the colors are black and white. This is going to be more difficult to compute with real colors. I might have to rethink how I do this. I could do things with absolute distances instead of percentages.
		@max_distance = 3 * @needle.columns * @needle.rows * PIXEL_COLOR_MAX
	end

	@@instance = Search.new

	def self.instance
		return @@instance
	end

	# Looks at some rectangle in the haystack image and determines how close it is to the needle image
	def distance(x, y, width, height)
		total_distance = 0

		# If the rectangle goes off the screen to the right, add the maximum possible distance for the pixels that overflow off the image
		new_width = width
		if x + width - 1 > @haystack.columns
			new_width = @haystack.columns - x
			total_distance += 3 * (width - new_width) * (height) * (PIXEL_COLOR_MAX + OFF_SCREEN_DISTANCE_PENALTY)
		end

		# If the rectangle goes off the screen to the left
		new_width = width
		if x < 0
			new_width = x + width
			total_distance += 3 * (width - new_width) * (height) * (PIXEL_COLOR_MAX + OFF_SCREEN_DISTANCE_PENALTY)
		end

		# Do the same for rectangles that go off the bottom of the screen
		new_height = height
		if y + height - 1 > @haystack.rows
			new_height = @haystack.rows - y
			total_distance += 3 * (height - new_height) * (width) * (PIXEL_COLOR_MAX + OFF_SCREEN_DISTANCE_PENALTY)
		end

		# If the rectangle goes off the screen on the top
		if y < 0
			new_height = y + height
			total_distance += 3 * (height - new_height) * (width) * (PIXEL_COLOR_MAX + OFF_SCREEN_DISTANCE_PENALTY)
		end

		# Now, compute the distance for the part of rectangle that is still on the search image
		width = new_width
		height = new_height

		# Loop through the rectangle, find the RGB value of each pixel in both the needle and the haystack. Compute the difference between the values and add it to total_distance
		for c in (x..x+width-1)
			for r in (y..y+height-1)
				haystackRGB = rgbFromPixel(@haystack.pixel_color(c, r))
				needleRGB = rgbFromPixel(@needle.pixel_color(c - x, r - y))

				total_distance += rgbDistance(haystackRGB, needleRGB)
			end
		end

		return total_distance
	end

	# Draws the haystack image to the screen
	def draw
		@haystack.columns.times do |column|
			@haystack.rows.times do |row|
				pixel = @haystack.pixel_color(column, row)
				
				Graphics.instance.screen.fill_rect(BORDER_X + column * PIXEL_SIZE, BORDER_Y + row * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, Graphics::instance.screen.mapRGB(pixel.red, pixel.green, pixel.blue))
			end
		end
	end
end
