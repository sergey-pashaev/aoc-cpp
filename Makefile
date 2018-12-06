.PHONY: test install-hooks

all:
	./scripts/build.sh

test:
	./scripts/tests.sh -DUSE_KCOV=0

coverage:
	./scripts/tests.sh

memcheck:
	./scripts/memcheck.sh -DUSE_KCOV=0

clean:
	rm -rf build/
