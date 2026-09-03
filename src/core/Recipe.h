#pragma once
#include "itemStack.h"


enum RecipeType {
	CRAFT,
	SMELT
};

class Recipe {
	ItemStack* ingredients[8];
	ItemStack* result;
	int craftingTicks;
	public:
		int getTime();
		ItemStack* getResult();
		ItemStack** getIngredients();
		Recipe(ItemStack** ingredients, ItemStack* result, int craftingTicks);
};

void registerRecipe(RecipeType category, Recipe* toAdd);

extern int numRecipes[256];
extern Recipe* recipeRegistry[256][256];