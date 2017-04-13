
$(BUILD_DIR)%.o: $(BASE)%.S
	$(Q)$(PRETTY) --dbuild "AS" $(MODULE_NAME) $(notdir $@)
	@mkdir -p $(dir $@)
	$(Q)$(AS) $(ASFLAGS) $< -o $@


