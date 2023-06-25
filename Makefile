SHARED_LIBRARY			:=		libappman.so
VAPI_FILE				:=		appman.vapi
HEADER_FILE				:=		appman.h

RCKTL_INSTALL_LIB_DIR	:=		/usr/lib/rapidlauncher
BUILD_DIR				:=		build
DIR_SOURCES				:=		src

PACKAGES				:=		gobject-2.0
PACKAGES				+=		glib-2.0
PACKAGES				+=		gio-2.0
PACKAGES				+=		x11
PACKAGES				+=		gtk+-3.0

GEN_FLAGS				:=		$(addprefix --pkg ,$(PACKAGES))
GEN_FLAGS				+=		--target-glib=2.32
GEN_FLAGS				+=		--ccode
GEN_FLAGS				+=		--header="$(BUILD_DIR)/$(HEADER_FILE)"
GEN_FLAGS				+=		--vapi="$(BUILD_DIR)/$(VAPI_FILE)"

CC_FLAGS				:=		-w
CC_FLAGS				+=		-fPIC
CC_FLAGS				+=		-shared
CC_FLAGS				+=		$(shell pkg-config --cflags $(PACKAGES))
CC_FLAGS				+=		-I$(BUILD_DIR)

LD_FLAGS				:=		-fPIC
LD_FLAGS				+=		-shared
LD_FLAGS				+=		$(shell pkg-config --libs $(PACKAGES))

SOURCES					:=		$(wildcard $(DIR_SOURCES)/*.vala)

OBJECTS					:=		${SOURCES:.vala=.o}
VAPIFILES				:=		${SOURCES:.vala=.vapi}


ifndef BUILD_DIR
	$(error variable BUILD_DIR is not set)
endif

ifndef RCKTL_INSTALL_LIB_DIR
	$(error variable RCKTL_INSTALL_LIB_DIR is not set)
endif

ifdef RCKTL_BUILD_DEBUG
	GEN_FLAGS				+=		--debug
	CC_FLAGS				+=		--debug
endif

ifdef RCKTL_BUILD_RELEASE
	CC_FLAGS				+=		-O3
endif


.SECONDARY:
	@#

.PHONY: all clean install uninstall
	@#


all: $(SOURCES) $(CFILES) $(BUILD_DIR)/$(SHARED_LIBRARY) $(BUILD_DIR)/$(VAPI_FILE) $(BUILD_DIR)/$(HEADER_FILE)
	@#

clean:
	rm -f ${SOURCES:.vala=.c}
	rm -f ${SOURCES:.vala=.h}
	rm -f ${SOURCES:.vala=.o}
	rm -f ${SOURCES:.vala=.vapi}
	rm -f "$(BUILD_DIR)/$(VAPI_FILE)"
	rm -f "$(BUILD_DIR)/$(HEADER_FILE)"
	rm -f "$(BUILD_DIR)/$(SHARED_LIBRARY)"

install:
	install -D "$(BUILD_DIR)/$(SHARED_LIBRARY)" "$(DESTDIR)$(RCKTL_INSTALL_LIB_DIR)/$(SHARED_LIBRARY)"

uninstall:
	rm -f "$(DESTDIR)$(RCKTL_INSTALL_LIB_DIR)/$(SHARED_LIBRARY)"


%.vapi: %.vala
	@echo "  GEN     $(notdir $@)"
	@valac --fast-vapi="$@" $<

MISSINGVAPIFILES=$(subst $(subst .c,.vapi,$@),,$(VAPIFILES))
$(BUILD_DIR)/$(HEADER_FILE):
$(BUILD_DIR)/$(VAPI_FILE):
%.c: $(MISSINGVAPIFILES) %.vala
	@echo "  GEN     $(notdir $@)"
	@valac $(GEN_FLAGS) $(addprefix --use-fast-vapi=,$(MISSINGVAPIFILES)) "$(subst .c,.vala,$@)"

%.o: %.c
	@echo "  CC      $(notdir $@)"
	@$(CC) $(CC_FLAGS) -c $< -o $@

$(BUILD_DIR)/$(SHARED_LIBRARY): $(OBJECTS)
	@echo "  LD      $(notdir $@)"
	@$(CC) $(OBJECTS) $(LD_FLAGS) -o "$(BUILD_DIR)/$(SHARED_LIBRARY)"

