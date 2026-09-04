#include "recipes.h"


// fuck it hardcode this shit or load it from a JSON no need to split out into files like the machines
void loadRecipes() {
	ItemStack* ingredients[8];

	ingredients[1] = NULL;

	ingredients[0] = new ItemStack(ITEM[8], 1);
	registerRecipe(SMELT, new Recipe(ingredients, new ItemStack(ITEM[9], 1), 50)); // SMELT RAW TIN

	ingredients[0] = new ItemStack(ITEM[9], 1);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[10], 1), 10)); // CRAFT: TIN SHEET

	ingredients[0] = new ItemStack(ITEM[9], 2);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[11], 1), 15)); // CRAFT: TIN GEAR

	ingredients[0] = new ItemStack(ITEM[10], 2);
	ingredients[1] = new ItemStack(ITEM[11], 1);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[1], 4), 20)); // CRAFT: CONVEYOR

	ingredients[0] = new ItemStack(ITEM[1], 1);
	ingredients[1] = new ItemStack(ITEM[10], 1);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[2], 1), 20)); // CRAFT: EXPORTER

	ingredients[0] = new ItemStack(ITEM[1], 1);
	ingredients[1] = new ItemStack(ITEM[10], 1);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[3], 1), 20)); // CRAFT: IMPORTER

	ingredients[0] = new ItemStack(ITEM[10], 4);
	ingredients[1] = new ItemStack(ITEM[9], 2);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[4], 1), 20)); // CRAFT: CRATE

	ingredients[0] = new ItemStack(ITEM[1], 2);
	ingredients[1] = new ItemStack(ITEM[10], 3);
	ingredients[2] = new ItemStack(ITEM[11], 2);
	ingredients[3] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[5], 2), 40)); // CRAFT: SPLITTER

	ingredients[0] = new ItemStack(ITEM[9], 5);
	ingredients[1] = new ItemStack(ITEM[11], 3);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[6], 1), 40)); // CRAFT: FURNACE

	ingredients[0] = new ItemStack(ITEM[10], 5);
	ingredients[1] = new ItemStack(ITEM[11], 10);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[7], 1), 40)); // CRAFT: TIN GENERATOR
}