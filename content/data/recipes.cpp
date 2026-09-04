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

	ingredients[0] = new ItemStack(ITEM[2], 4);
	ingredients[1] = new ItemStack(ITEM[1], 3);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[5], 1), 48));

	ingredients[0] = new ItemStack(ITEM[3], 4);
	ingredients[1] = new ItemStack(ITEM[1], 3);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[5], 1), 48));

	ingredients[0] = new ItemStack(ITEM[1], 1);
	ingredients[1] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[2], 1), 21));

	ingredients[0] = new ItemStack(ITEM[1], 1);
	ingredients[1] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[3], 1), 19));

	ingredients[0] = new ItemStack(ITEM[1], 1);
	ingredients[1] = new ItemStack(ITEM[2], 1);
	ingredients[2] = new ItemStack(ITEM[3], 1);
	ingredients[3] = new ItemStack(ITEM[4], 1);
	ingredients[4] = new ItemStack(ITEM[5], 1);
	ingredients[5] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[6], 10), 19));

	ingredients[0] = new ItemStack(ITEM[6], 2);
	ingredients[1] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[7], 1), 2));


	ingredients[0] = new ItemStack(ITEM[7], 2);
	ingredients[1] = NULL;
	registerRecipe(SMELT, new Recipe(ingredients, new ItemStack(ITEM[6], 1), 80));

	ingredients[0] = new ItemStack(ITEM[4], 1);
	ingredients[1] = NULL;
	registerRecipe(SMELT, new Recipe(ingredients, new ItemStack(ITEM[5], 1), 20));
}