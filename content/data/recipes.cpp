#include "recipes.h"


// fuck it hardcode this shit or load it from a JSON no need to split out into files like the machines
void loadRecipes() {
	ItemStack* ingredients[8];

	ingredients[1] = NULL;

	ingredients[0] = new ItemStack(ITEM[8], 1);
	registerRecipe(SMELT, new Recipe(ingredients, new ItemStack(ITEM[9], 1), 50));

	ingredients[0] = new ItemStack(ITEM[9], 1);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[10], 1), 20));

	ingredients[0] = new ItemStack(ITEM[9], 2);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[11], 1), 30));

	ingredients[0] = new ItemStack(ITEM[10], 2);
	ingredients[1] = new ItemStack(ITEM[11], 1);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[1], 1), 20));

	ingredients[0] = new ItemStack(ITEM[1], 1);
	ingredients[1] = new ItemStack(ITEM[10], 1);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[2], 1), 20));

	ingredients[0] = new ItemStack(ITEM[1], 1);
	ingredients[1] = new ItemStack(ITEM[10], 1);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[3], 1), 20));

	ingredients[0] = new ItemStack(ITEM[1], 2);
	ingredients[1] = new ItemStack(ITEM[10], 3);
	ingredients[2] = new ItemStack(ITEM[11], 2);
	ingredients[3] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[5], 2), 40));

	ingredients[0] = new ItemStack(ITEM[10], 5);
	ingredients[1] = new ItemStack(ITEM[11], 3);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[6], 1), 40));

	ingredients[0] = new ItemStack(ITEM[10], 5);
	ingredients[1] = new ItemStack(ITEM[11], 10);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[7], 1), 40));
}