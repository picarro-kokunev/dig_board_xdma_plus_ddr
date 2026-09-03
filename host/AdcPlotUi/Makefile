# AdcPlotUi build helpers
#
# Typical workflow:
#   make publish      # single-file binary in dist/
#   make run-local    # publish and run on this machine

PROJECT      := AdcPlotUi
PROJECT_FILE := $(PROJECT).csproj
CONFIG       ?= Release
RID          ?= linux-x64
DIST         := dist
BINARY       := $(DIST)/$(PROJECT)
XDMA_INDEX   ?= 0

DOTNET_PUBLISH_FLAGS := \
	-c $(CONFIG) \
	-r $(RID) \
	--self-contained true \
	-p:PublishSingleFile=true \
	-p:IncludeNativeLibrariesForSelfExtract=true \
	-p:EnableCompressionInSingleFile=true \
	-o $(DIST)

.PHONY: all build publish run-local clean help

all: publish

help:
	@echo "Targets:"
	@echo "  build       Debug/Release compile (framework-dependent)"
	@echo "  publish     Self-contained single-file binary -> $(BINARY)"
	@echo "  run-local   Run published binary on this machine"
	@echo "  clean       Remove build outputs"
	@echo ""
	@echo "Variables: CONFIG=$(CONFIG) RID=$(RID) XDMA_INDEX=$(XDMA_INDEX)"

build:
	dotnet build $(PROJECT_FILE) -c $(CONFIG)

publish:
	dotnet publish $(PROJECT_FILE) $(DOTNET_PUBLISH_FLAGS)
	@echo "Published: $(BINARY)"

run-local: publish
	$(BINARY) --xdma-index $(XDMA_INDEX)

clean:
	dotnet clean $(PROJECT_FILE) -c $(CONFIG)
	rm -rf bin obj $(DIST)
