Agents Agents::instance;

Agents &Agents::getInstance() {
	return instance;
}

void Agents::init() {
	best_percentage = 100;
}

int Agents::get_best_percentage() {
	return best_percentage;
}

void Agents::new_percentage(int percentage) {
	if(percentage < best_percentage) {
		best_percentage = percentage;
	}
}

void Agents::add(int index, Agent agent) {
	agents[index] = agent;
}

Agent Agents::random_agent() {
	return agents[rand() % NUM_AGENTS];
}

void Agents::update_state() {
	for(int i = 0; i < NUM_AGENTS; i++) {
		agents[i].update_state();
	}
}

void Agents::update() {
	for(int i = 0; i < NUM_AGENTS; i++) {
		agents[i].update();
	}
}

void Agents::draw() {
	for(int i = 0; i < NUM_AGENTS; i++) {
		agents[i].draw();
	}

}
