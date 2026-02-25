#pragma once

namespace Models {
	// Ressources matérielles produites ou consommées par les bâtiments. ATTENTION : on l'écrit avec un seul "s", à l'anglaise, pour rester cohérent avec le reste de la nomenclature des classes
	enum class Resource {
		// --- Nourriture ---
		// Nourriture basique
		Grain,
		Legumes,
		Fruits,
		Viande,
		// Ingrédient de nourriture transformée
		Farine,
		Epices,
		// Nourriture transformée
		Pain,
		Patisserie,
		Mets,
		// --- Biens de consommation ---
		// Production primaire
		Teinture,
		Cuir,
		Laine,
		Fer,
		Or,
		// Produits transformés
		Biere,
		Liqueur,
		Ferronnerie,
		Armes,
		Bijoux,
		Tissu,
		Draps,
		Maroquinerie,
		Parchemin,
	};
}