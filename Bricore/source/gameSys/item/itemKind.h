#pragma once

namespace item {
	class Enerma;
	class Chip;
	class Core;
	template<typename T> class ItemKind;

	// area item
	template<> class ItemKind<Enerma> {
	public:
		enum Kind {
			AttackEnerma,
			CoolDownEnerma,
			DefendEnerma,
			HealEnerma,
			lifeEnerma,
			ReviveEnerma,
		};
	};
	// be used on subplayer to change type
	template<> class ItemKind<Chip> {
	public:
		enum Kind {
			None,
			BurstChip,
			FirearmChip,
			GuardChip,
			HeraldChip,
			LaserChip,
		};
	};
	// boss core to change boss type
	template<> class ItemKind<Core> {
	public:
		enum Kind {
			alphaCore,
			betaCore,
			GammaCore,
			DeltaCore,
			EpsilonCore,
			ZetaCore,
			EtaCore,
			LotaCore,
			KappaCore
		};
	};
}