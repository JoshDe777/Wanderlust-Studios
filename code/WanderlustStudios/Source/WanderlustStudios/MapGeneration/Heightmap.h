#pragma once

namespace WanderlustStudios::MapGeneration {
	class Heightmap {
		friend class AA_MapManager;
	public:
		explicit Heightmap(std::pair<int, int> dimensions);
		explicit Heightmap(std::vector<float>& const primitive);
		void UpscaleAndBlur();
		int dimensions();
		const std::vector<float> values() const { /*return a const copy*/ return const std::vector<float>(_values); }
		void apply_additive(DiffNet* image, float weight);
	private:
		std::vector<float> _values;
	};
}
