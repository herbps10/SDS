class Agents {
	public:
		static Agents &getInstance();
		int get_best_percentage();
		void new_percentage(int percentage);
		void init();
		void add(int index, Agent agent);
		Agent random_agent();
		void update_state();
		void update();
		void draw();

	private:
		static Agents instance;
		Agent agents[NUM_AGENTS];
		int best_percentage;
};
