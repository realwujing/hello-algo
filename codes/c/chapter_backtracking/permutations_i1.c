void backtrack(State *state, Choice *choices, int numChoices, State *res, int numRes) {
	if (isSolution(state)) {
		recordSolution(state, res, numRes);
		return;
	}

	for (int i = 0; i < numChoices; i++) {
		if (isValid(state, &chioces[i])) {
			makeChoice(state, &chioces[i]);
			backtrack(state, choices, numChoices, res, numRes);
			undoChoice(state, &choices[i]);
		}
	}
}
