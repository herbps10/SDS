// SDS Settings
const int NUM_AGENTS = 50; // Number of agnets
const int ACTIVE_THRESHOLD = 50; // The distance percentage must be less than this number in order for an agent to be in active.

// Paths to the base images
const string NEEDLE_PATH = "images/people.png";
const string HAYSTACK_PATH = "images/people-needle.png";

const int START_BEST_PERCENTAGE = 30;

// Graphics Settings
const bool FULLSCREEN = false;

int SCREEN_WIDTH = 1200;
int SCREEN_HEIGHT = 600;

const int BORDER_X = 40;
const int BORDER_Y = 40;

const int PIXEL_SIZE = 1; // How large each pixel from the search image should appear on the screen. Set to this to 1 for no scaling.

const int PIXEL_COLOR_MAX = 255;
const int OFF_SCREEN_DISTANCE_PENALTY = 100;

const int AGENT_BORDER_WIDTH_ACTIVE = 3;
const int AGENT_BORDER_WIDTH_INACTIVE = 1;

const int UPDATE_FRAME = 1; // How many frames to wait before updating the agents. Set to 1 for the search to go as fast as possible.
