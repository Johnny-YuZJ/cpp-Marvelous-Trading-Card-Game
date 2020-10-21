CXX=g++-5
CXXFLAGS=-std=c++14	-Wall	-MMD
OBJECTS=main.o board.o	game.o player.o ./display/ascii_graphics.o	./display/display.o	./display/window.o ./card/card.o ./card/deck_generator.o ./card/spell/banish.o ./card/spell/blizzard.o ./card/spell/disenchant.o ./card/spell/novicefireball.o ./card/spell/raisedead.o ./card/spell/recharge.o ./card/spell/spell.o ./card/spell/summon.o ./card/spell/summonthree.o ./card/spell/unsummon.o ./card/ritual/ritual.o ./card/ritual/auraofpower.o ./card/ritual/darkritual.o ./card/ritual/standstill.o ./card/minion/minion.o ./card/minion/normal_minion.o ./card/minion/air_elemental.o ./card/minion/apprentice_summoner.o ./card/minion/bone_golem.o ./card/minion/earth_elemental.o ./card/minion/enchant_enrage.o ./card/minion/enchant_giant_strength.o ./card/minion/enchant_haste.o ./card/minion/enchant_magic_fatigue.o ./card/minion/enchant_silence.o ./card/minion/enchanted_minion.o ./card/minion/fire_elemental.o ./card/minion/master_summoner.o ./card/minion/novice_pyromancer.o ./card/minion/potion_seller.o ./card/enchantment/enchantment.o ./card/enchantment/enrage.o ./card/enchantment/giant_strength.o ./card/enchantment/haste.o ./card/enchantment/magic_fatigue.o ./card/enchantment/silence.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=run

${EXEC}:	${OBJECTS}
	${CXX}	${CXXFLAGS}	${OBJECTS}	-o	${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm *.o main
.PHONY: clean
