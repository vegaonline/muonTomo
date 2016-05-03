.PHONY: clean All

All:
	@echo "----------Building project:[ MuonTomo - Debug ]----------"
	@cd "MuonTomo" && "$(MAKE)" -f  "MuonTomo.mk"
clean:
	@echo "----------Cleaning project:[ MuonTomo - Debug ]----------"
	@cd "MuonTomo" && "$(MAKE)" -f  "MuonTomo.mk" clean
