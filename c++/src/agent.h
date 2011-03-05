// Encapsulates an individual agent

class Agent {
	public:
		Agent();
		Agent(int newx, int newy, int newwidth, int newheight);

		int fitness(); // Converts the absolute distance to a percent

		void update_state(); // Updates whether the agent is active/inactive
		void update(); // Updates the position of the agent, if necessary

		void randomize(); // Randomizes the position of the agent
		void move_vicinity(); // Moves the agent to somewhere in its immediate vicinity

		void draw(); // Draws a graphical representation of the agent to the SDL screen

		bool is_active();
		int get_x();
		int get_y();

	private:
		int x, y, width, height;
		bool active;
};
