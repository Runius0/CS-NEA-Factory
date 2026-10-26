#include "recipes.h"


// fuck it hardcode this shit or load it from a JSON no need to split out into files like the machines
void loadRecipes() {
	ItemStack* ingredients[8];

	ingredients[1] = NULL;

	ingredients[0] = new ItemStack(ITEM[IT_ORE_TIN], 1);
	registerRecipe(SMELT, new Recipe(ingredients, new ItemStack(ITEM[IT_BLOCK_TIN], 1), 50)); // SMELT RAW TIN

	ingredients[0] = new ItemStack(ITEM[IT_ORE_COPPER], 1);
	registerRecipe(SMELT, new Recipe(ingredients, new ItemStack(ITEM[IT_BLOCK_COPPER], 1), 50)); // SMELT RAW COPPER

	ingredients[0] = new ItemStack(ITEM[IT_ORE_ZINC], 1);
	registerRecipe(SMELT, new Recipe(ingredients, new ItemStack(ITEM[IT_BLOCK_ZINC], 1), 50)); // SMELT RAW ZINC


	// CRAFT SHEETS
	ingredients[1] = NULL;

	ingredients[0] = new ItemStack(ITEM[IT_BLOCK_TIN], 1);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_SHEET_TIN], 1), 10));

	ingredients[0] = new ItemStack(ITEM[IT_BLOCK_COPPER], 1);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_SHEET_COPPER], 1), 10));

	ingredients[0] = new ItemStack(ITEM[IT_BLOCK_ZINC], 1);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_SHEET_ZINC], 1), 10));


	// CRAFT GEARS
	ingredients[0] = new ItemStack(ITEM[IT_BLOCK_TIN], 2);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_GEAR_TIN], 1), 15)); 

	ingredients[0] = new ItemStack(ITEM[IT_BLOCK_TIN], 2);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_GEAR_COPPER], 1), 15));

	ingredients[0] = new ItemStack(ITEM[IT_BLOCK_TIN], 2);
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_GEAR_ZINC], 1), 15));


	ingredients[0] = new ItemStack(ITEM[IT_SHEET_TIN], 2);
	ingredients[1] = new ItemStack(ITEM[IT_GEAR_TIN], 1);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_CONVEYOR], 4), 20)); // CRAFT: CONVEYOR

	ingredients[0] = new ItemStack(ITEM[1], 1);
	ingredients[1] = new ItemStack(ITEM[IT_SHEET_TIN], 1);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_EXPORTER], 1), 20)); // CRAFT: EXPORTER

	ingredients[0] = new ItemStack(ITEM[1], 1);
	ingredients[1] = new ItemStack(ITEM[IT_SHEET_TIN], 1);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_IMPORTER], 1), 20)); // CRAFT: IMPORTER

	ingredients[0] = new ItemStack(ITEM[IT_SHEET_COPPER], 4);
	ingredients[1] = new ItemStack(ITEM[IT_BLOCK_ZINC], 2);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[IT_CRATE], 1), 20)); // CRAFT: CRATE

	ingredients[0] = new ItemStack(ITEM[1], 2);
	ingredients[1] = new ItemStack(ITEM[IT_SHEET_TIN], 3);
	ingredients[2] = new ItemStack(ITEM[IT_GEAR_COPPER], 2);
	ingredients[3] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[5], 2), 40)); // CRAFT: SPLITTER

	ingredients[0] = new ItemStack(ITEM[IT_BLOCK_TIN], 5);
	ingredients[1] = new ItemStack(ITEM[IT_SHEET_COPPER], 5);
	ingredients[2] = NULL;
	registerRecipe(CRAFT, new Recipe(ingredients, new ItemStack(ITEM[6], 1), 40)); // CRAFT: FURNACE
}