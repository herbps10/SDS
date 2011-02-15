# SDS Settings
NUM_AGENTS = 50 # Number of agnets
ACTIVE_THRESHOLD = 50 # The distance percentage must be less than this number in order for an agent to be in active.

# Paths to the base images
NEEDLE_PATH = 'images/people.png'
HAYSTACK_PATH = 'images/people-needle.png'

START_BEST_PERCENTAGE = 30

# Graphics Settings
SCREEN_WIDTH = 1000
SCREEN_HEIGHT = 1000

BORDER_X = 40
BORDER_Y = 40

PIXEL_SIZE = 3 # How large each pixel from the search image should appear on the screen. Set to this to 1 for no scaling.

PIXEL_COLOR_MAX = 255
OFF_SCREEN_DISTANCE_PENALTY = 100

AGENT_BORDER_WIDTH_ACTIVE = 3
AGENT_BORDER_WIDTH_INACTIVE = 1

UPDATE_FRAME = 1 # How many frames to wait before updating the agents. Set to 1 for the search to go as fast as possible.


