class Agent
	attr_accessor :x, :y

	def initialize(x, y, width, height)
		@x = x
		@y = y
		@width = width
		@height = height

		@active = false

		self
	end

	def active?
		return @active
	end
	
	def distance()
		return Search::instance.distance(@x, @y, @width, @height)
	end

	def distance_percent()
		return (100 * distance()) / Search::instance.max_distance
	end

	def draw()
		border_color = Graphics::instance.screen.mapRGB(255, 0, 0)
		if @active == true
			border_color = Graphics::instance.screen.mapRGB(0, 255, 0)
		end

		border_width = AGENT_BORDER_WIDTH_INACTIVE
		border_width = AGENT_BORDER_WIDTH_ACTIVE if active?

		border_width.times do |i|
			Graphics::instance.screen.draw_rect(i + BORDER_X + @x * PIXEL_SIZE, i + BORDER_Y + @y * PIXEL_SIZE, @width * PIXEL_SIZE - 1, @height * PIXEL_SIZE - 1, border_color)
		end

		#Graphics::instance.font.drawBlendedUTF8(Graphics::instance.screen, distance_percent().to_s, BORDER_X + @x * PIXEL_SIZE, BORDER_Y + @y * PIXEL_SIZE, 150, 150, 150)
	end

	def randomize
		@x = (rand() * Search::instance.haystack.columns).to_i
		@y = (rand() * Search::instance.haystack.rows).to_i
		self
	end

	def update_state
		if distance_percent <= Agents::instance.best_percentage
			Agents::instance.new_percentage(distance_percent)

			@active = true

			# Small chance the agent will randomly switch to inactive
			if rand(10) == 1
				@active = false
			end
		else
			@active = false
		end
	end

	def move_vicinity
		# The agent can move either -1, 0, or 1 pixels in any direction
		dx = rand(3) - 1
		dy = rand(3) - 1

		@x += dx
		@y += dy
	end

	def update
		# for now, just randomly change position
		if @active
			# Have a random chance that the agent will move to a slightly different location in the immediate vicinity
			if rand(10) == 1
				#move_vicinity
				#update_state
			end
		else
			random_agent = Agents::instance.random_agent
			
			if random_agent.active?
				@x = random_agent.x
				@y = random_agent.y
			else
				if rand(3) == 1
					randomize
				else
					move_vicinity
				end
			end
		end
	end
end
