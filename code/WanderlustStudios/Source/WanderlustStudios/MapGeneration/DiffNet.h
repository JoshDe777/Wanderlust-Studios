#pragma once

#include <vector>
#include <memory>
#include <unordered_map>
#include <random>

namespace WanderlustStudios::MapGeneration {
	/// The default width of the diffusion net grid.
	const int BASE_WIDTH = 4;

	/// Utility struct representing a pixel entry to the Diffusion Net.
	class DiffNetPixel {
	public:
		/// Creates a new DiffNetPixel object.
		/// @param coords: std::pair<int, int> - the (x, y) coords of the pixel in grid space.
		/// @param pred: DiffNetPixel* - A pointer to the pixel it is attached to. May be null.
		explicit DiffNetPixel(std::pair<int, int> coords, DiffNetPixel* pred = nullptr) : gridCoords(coords), predecessor(pred) { }

		/// the (x, y) coords of the pixel in grid space.
		std::pair<int, int> gridCoords;
		/// A pointer to the pixel it is attached to. May be null.
		DiffNetPixel* predecessor;
	};

	/// A class representing a grid of pixels generated through diffusion-layer aggregation
	class DiffNet {
		// MapManager has access to private members for map generation purposes.
		friend class AA_MapManager;
	public:
		/// Constructor. Builds a BASE_WIDTH x BASE_WIDTH empty grid.
		explicit DiffNet(std::pair<int, int> dims = {BASE_WIDTH, BASE_WIDTH});

		/// Outputs the (x, y) dimensions of the Diffusion Net.
		std::pair<int, int> Dimensions() const { return dimensions; }
		/// Outputs the amount of cells in the diffusion net (x * y)
		int FlatDimensions() const { return dimensions.first * dimensions.second; }
		/// Counts the amount of populated pixels currently in the net.
		float Sum() const { return pixels.size(); }
		/// Outputs the proportion of cells currently filled with pixels.
		float GetFill() const { return (float) Sum() / (float) FlatDimensions(); }

		/// Doubles the net in size, and interpolates new pixels between previously connected ones, with some jittering.
		void Upscale(std::mt19937& rnd);

		/// Returns a flat list of pixels that are populated.
		std::vector<DiffNetPixel*> Enumerate() const;
		/// returns a list of coordinates not yet part of the diffusion net.
		std::vector<std::pair<int, int>>& GetUnmarkedPixels() { return unmapped_pixels; }

		/// Determines whether a given coordinate is part of the diffusion net.
		bool Contains(std::pair<int, int>& coord) const;
		/// Returns the pixel object at a given coordinate. Returns nullptr if no such object exists.
		DiffNetPixel* Find(std::pair<int, int>& coord) const;
		/// Checks whether a given coordinate is in bounds for the given DiffNet.
		bool InBounds(std::pair<int, int>& coord) const;

		/// Introduces a pixel as a 'starter' pixel (has no predecessor - will be a mountain peak)
		void MarkStarter(std::pair<int, int>& coord);
		/// Introduces a pixel as a sequel of its predecessor.
		DiffNetPixel* Mark(std::pair<int, int>& coord, DiffNetPixel* predecessor);
	private:
		/// Returns a new DiffNet object with the exact same attributes.
		DiffNet Copy() const;

		/// The (x, y) size of the grid.
		std::pair<int, int> dimensions;
		/// A lookup list of coordinates not yet covered by a pixel.
		std::vector<std::pair<int, int>> unmapped_pixels;
		/// Keeps a reference of pixels' index in the pixels list to their coordinate in grid space.
		std::unordered_map<std::pair<int, int>, int> pixel_lookup = {};
		/// A list of existing pixels, proprietary to a given DiffNet.
		std::vector<std::unique_ptr<DiffNetPixel>> pixels = {};
	};
}
