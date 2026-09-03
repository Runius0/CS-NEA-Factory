#include "Recipe.h"


int numRecipes[256];
Recipe* recipeRegistry[256][256];

ItemStack* Recipe::getResult() {
	return result;
}
int Recipe::getTime() {
	return craftingTicks;
}
ItemStack** Recipe::getIngredients() {
	return ingredients;
}

Recipe::Recipe(ItemStack** _ingredients, ItemStack* _result, int _craftingTicks) {
	for (int i = 0; i < 8; i++) {
		ingredients[i] = _ingredients[i];
		if (_ingredients[i] == NULL) {
			break;
		}
	}
	result = _result;
	craftingTicks = _craftingTicks;

};


void registerRecipe(RecipeType category, Recipe* toAdd) {
	int ID = numRecipes[category];
	recipeRegistry[category][ID] = toAdd;
	numRecipes[category]++;
};