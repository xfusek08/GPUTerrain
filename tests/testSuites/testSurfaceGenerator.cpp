
#include <catch.hpp>

#include <memory>

#include <GeoPlanetLib/SurfaceGenerator.h>
#include <GeoPlanetLib/modifiers/modifiers.h>

using namespace gp;
using namespace gp::modifiers;
using namespace std;

bool modifierListsEquals(const ModifierList& l1, const ModifierList& l2)
{
    return equal(
        l1.begin(), l1.end(),
        l2.begin(), l2.end(),
        [](ModifierListItem item1, ModifierListItem item2) {
            return item1.ident == item2.ident
                && item1.enabled == item2.enabled
                && item1.modifier != nullptr
                && item2.modifier != nullptr;
        }
    );
}

bool modifierListsCorrespodsToConfig(const ModifierList& l1, const vector<string>&  config)
{
	if (l1.size() != config.size()) {
		return false;
	}

	unsigned int index = 0;
	for (auto ident : config) {
        auto actItem = l1[index];
        if (actItem.ident != ident) {
            return false;
        }
		index++;
    }
    return true;
}

template<class T>
void assertModifierExists(string ident, SurfaceGenerator generator)
{
    shared_ptr<T> modifier;
	auto item = generator.getModifier(ident);
	REQUIRE(item.enabled);
	REQUIRE(item.ident == ident);
	REQUIRE_NOTHROW(modifier = dynamic_pointer_cast<T>(item.modifier));
}

void assertModifierDontExists(string ident, SurfaceGenerator generator)
{
    auto item = generator.getModifier("");
	REQUIRE_FALSE(item.enabled);
	REQUIRE(item.ident == "");
	REQUIRE(item.modifier == nullptr);
}

class SurfaceModifierShim : public SurfaceModifier
{
public:
    // propertires
    bool valid = false;
    bool called = false;
    bool returnValue = true;

    // methods
    bool apply(std::shared_ptr<Surface> surface) override
    {
        called = true;

        valid = surface != nullptr
            && surface->getResolution() > 0
            && surface->getRegions().size() > 0;

        return returnValue;
    }

    void reset()
    {
        valid = false;
        called = false;
    }
};

// =============================================================================
// TESTS
// =============================================================================

TEST_CASE("test constructor defaults") {
    auto generator1 = SurfaceGenerator();
	auto generator2 = SurfaceGenerator(DEFAULT_MODIFIER_CONFIG);

	REQUIRE(modifierListsCorrespodsToConfig(
        generator1.getModifiers(), DEFAULT_MODIFIER_CONFIG
    ));

	REQUIRE(modifierListsEquals(
        generator1.getModifiers(),
        generator2.getModifiers()
    ));
}

TEST_CASE("test constructor config valid for each defined modifier") {
    auto modifiers = SurfaceModifier::list();
    SurfaceGenerator generator;

    REQUIRE_NOTHROW(generator = SurfaceGenerator(vector<string>{}));
    REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), {}));

    for (auto modifierIdent : modifiers) {
        REQUIRE_NOTHROW(generator = SurfaceGenerator({modifierIdent}));
        REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { modifierIdent }));
    }
    REQUIRE_NOTHROW(generator = SurfaceGenerator(modifiers));
    REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), modifiers));
}

TEST_CASE("test constructor config invalid") {
    REQUIRE_THROWS_AS(SurfaceGenerator({ "" }), invalid_argument);
    REQUIRE_THROWS_AS(SurfaceGenerator({ "asd" }), invalid_argument);
}

TEST_CASE("test constructor config valid for multiple same modifiers") {
    SurfaceGenerator generator;
    REQUIRE_NOTHROW(generator = SurfaceGenerator({
		"JitterModifier",
		"JitterModifier",
		"RandomColorModifier"
	}));

    REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), {
		"JitterModifier",
		"RandomColorModifier"
	}));

    REQUIRE_NOTHROW(generator = SurfaceGenerator({
		"JitterModifier",
		"RandomColorModifier",
		"JitterModifier"
	}));

	REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), {
		"JitterModifier",
		"RandomColorModifier",
	}));
}

TEST_CASE("test get modifiers") {
    SurfaceGenerator generator;
    REQUIRE_NOTHROW(generator = SurfaceGenerator({"JitterModifier", "RandomColorModifier"}));
    auto modifierList = generator.getModifiers();
    REQUIRE(modifierListsCorrespodsToConfig(modifierList, {"JitterModifier", "RandomColorModifier"}));

	shared_ptr<JitterModifier> jm;
	shared_ptr<RandomColorModifier> rcm;
    REQUIRE_NOTHROW(jm = dynamic_pointer_cast<JitterModifier>(modifierList[0].modifier));
    REQUIRE_NOTHROW(rcm = dynamic_pointer_cast<RandomColorModifier>(modifierList[1].modifier));
}

TEST_CASE("test get modifier") {
    auto generator = SurfaceGenerator({"JitterModifier", "RandomColorModifier"});
    assertModifierExists<JitterModifier>("JitterModifier", generator);
    assertModifierExists<RandomColorModifier>("RandomColorModifier", generator);
    assertModifierDontExists("", generator);
    assertModifierDontExists("asd", generator);
}

TEST_CASE("test add modifiers") {
	auto generator = SurfaceGenerator({ "RandomColorModifier" });

	REQUIRE_NOTHROW(generator.addModifier("JitterModifier"));
    assertModifierExists<JitterModifier>("JitterModifier", generator);

	auto modifierList = generator.getModifiers();
	REQUIRE(modifierListsCorrespodsToConfig(modifierList, { "RandomColorModifier", "JitterModifier" }));
	REQUIRE_FALSE(modifierListsCorrespodsToConfig(modifierList, { "JitterModifier", "RandomColorModifier" }));
}

TEST_CASE("test remove modifier") {
	auto generator = SurfaceGenerator({ "JitterModifier", "RandomColorModifier" });
	REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { "JitterModifier", "RandomColorModifier" }));

    REQUIRE(generator.removeModifier("RandomColorModifier"));
	REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { "JitterModifier" }));

    REQUIRE_FALSE(generator.removeModifier(""));
	REQUIRE_FALSE(generator.removeModifier("asd"));
	REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { "JitterModifier" }));

    REQUIRE(generator.removeModifier("JitterModifier"));
	REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), {}));
	REQUIRE_FALSE(generator.removeModifier("JitterModifier"));
}

TEST_CASE("test adding and deleteing modifiers with same type under different names") {
	SurfaceGenerator generator = SurfaceGenerator(vector<string>{});
    generator.addModifier("m1", "JitterModifier");
    generator.addModifier("m2", "RandomColorModifier");
    generator.addModifier("m3", "JitterModifier");
    generator.addModifier("m1", "RandomColorModifier");

    REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { "m1", "m2", "m3" }));

    assertModifierExists<RandomColorModifier>("m1", generator);
    assertModifierExists<RandomColorModifier>("m2", generator);
    assertModifierExists<JitterModifier>("m3", generator);

    REQUIRE(generator.removeModifier("m1"));
    REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { "m2", "m3" }));
    assertModifierDontExists("m1", generator);
    assertModifierExists<RandomColorModifier>("m2", generator);
    assertModifierExists<JitterModifier>("m3", generator);

    generator.addModifier("m1", "JitterModifier");
    REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { "m2", "m3", "m1" }));
    assertModifierExists<JitterModifier>("m1", generator);
    assertModifierExists<RandomColorModifier>("m2", generator);
    assertModifierExists<JitterModifier>("m3", generator);

    generator.addModifier("m3", "RandomColorModifier");
    REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { "m2", "m3", "m1" }));
    assertModifierExists<JitterModifier>("m1", generator);
    assertModifierExists<RandomColorModifier>("m2", generator);
    assertModifierExists<RandomColorModifier>("m3", generator);
}

TEST_CASE("test gest adding custom modifier instance") {
	SurfaceGenerator generator = SurfaceGenerator(vector<string>{});

    auto myJitterModifier = make_shared<JitterModifier>();
    generator.addModifier("m1", myJitterModifier);
    REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { "m1" }));
    assertModifierExists<JitterModifier>("m1", generator);
    auto item = generator.getModifier("m1");
    REQUIRE(item.modifier == myJitterModifier);

    auto myRandomColorModifier = make_shared<RandomColorModifier>();
    generator.addModifier("m1", myRandomColorModifier, false);
    REQUIRE(modifierListsCorrespodsToConfig(generator.getModifiers(), { "m1" }));
    auto item2 = generator.getModifier("m1");
    REQUIRE_FALSE(item2.enabled);
    REQUIRE(item2.modifier == myRandomColorModifier);
}

TEST_CASE("test disable enable modifier") {
	auto generator = SurfaceGenerator(vector<string>{});
    generator.addModifier("m1", "JitterModifier", true);
    generator.addModifier("m2", "RandomColorModifier", false);
    generator.addModifier("m3", "JitterModifier", false);
    generator.addModifier("m4", "RandomColorModifier", true);

    auto modifierList = generator.getModifiers();
    REQUIRE(modifierList[0].enabled);
    REQUIRE_FALSE(modifierList[1].enabled);
    REQUIRE_FALSE(modifierList[2].enabled);
    REQUIRE(modifierList[3].enabled);

    REQUIRE(generator.getModifier("m1").enabled);
    REQUIRE(generator.getModifier("m4").enabled);
    REQUIRE_FALSE(generator.getModifier("m2").enabled);
    REQUIRE_FALSE(generator.getModifier("m3").enabled);

	REQUIRE(generator.disableModifier("m1"));
    REQUIRE_FALSE(generator.getModifier("m1").enabled);

	REQUIRE(generator.enableModifier("m2"));
    REQUIRE(generator.getModifier("m2").enabled);

	REQUIRE_FALSE(generator.enableModifier(""));
	REQUIRE_FALSE(generator.enableModifier("asd"));
	REQUIRE_FALSE(generator.disableModifier(""));
	REQUIRE_FALSE(generator.disableModifier("asd"));
}

TEST_CASE("test generate") {
	auto generator = SurfaceGenerator({ "JitterModifier", "RandomColorModifier" });

	shared_ptr<Surface> surface;

    surface = generator.generate();
    REQUIRE(surface != nullptr);
    REQUIRE(surface->getResolution() == Surface::DEFAULT_RESOLUTION);

    surface = generator.generate(0);
    REQUIRE(surface != nullptr);
    REQUIRE(surface->getResolution() == Surface::DEFAULT_RESOLUTION);

	surface = generator.generate(15);
	REQUIRE(surface != nullptr);
    REQUIRE(surface->getResolution() == 15);
}

TEST_CASE("test apply modifiers") {
    auto generator = SurfaceGenerator(vector<string>{});

    auto surface = make_shared<Surface>();

    auto modifierValid = make_shared<SurfaceModifierShim>();
    auto modifierInvalid = make_shared<SurfaceModifierShim>();
    auto modifierValid2 = make_shared<SurfaceModifierShim>();

    modifierInvalid->returnValue = false;

    generator.addModifier("modifierValid", modifierValid);
    generator.addModifier("modifierInvalid", modifierInvalid, false);
    generator.addModifier("modifierDisabled", modifierValid2);

    REQUIRE(generator.applyModifiers(surface));

    REQUIRE(modifierValid->valid);
    REQUIRE_FALSE(modifierInvalid->called);
    REQUIRE(modifierValid2->valid);

    modifierValid->reset();
    modifierInvalid->reset();
    modifierValid2->reset();

    generator.enableModifier("modifierInvalid");
    REQUIRE_FALSE(generator.applyModifiers(surface));

    REQUIRE(modifierValid->valid);
    REQUIRE(modifierInvalid->valid);
    REQUIRE_FALSE(modifierValid2->called);
}
