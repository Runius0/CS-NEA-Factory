#include "recipes.h"


// fuck it hardcode this shit or load it from a JSON no need to split out into files like the machines
void loadRecipes() {
	ItemStack* ingredients[8];
	ingredients[1] = NULL;
	ingredients[0] = new ItemStack(ITEM[2], 2);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[1], 1), 10));
	ingredients[0] = new ItemStack(ITEM[3], 2);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[1], 2), 10));
	ingredients[0] = new ItemStack(ITEM[4], 1);
	ingredients[1] = new ItemStack(ITEM[1], 3);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[5], 1), 48));
}