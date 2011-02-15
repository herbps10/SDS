class Graphics
	attr_accessor :screen, :font

	def initialize
		SDL.init SDL::INIT_VIDEO
		@screen = SDL::set_video_mode(SCREEN_WIDTH, SCREEN_HEIGHT, 24, SDL::SWSURFACE)

		SDL::TTF.init
		@font = SDL::TTF.open("Existence-Light.ttf", 12, 0)
	end

	@@instance = Graphics.new

	def self.instance
		return @@instance
	end

	private_class_method :new
end


