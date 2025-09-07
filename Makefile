obj-m += ex_timer.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

all: modules

modules:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

format:
	clang-format -i *.c *.h

check:
	@echo "Проверка синтаксиса..."
	@$(MAKE) -C $(KDIR) M=$(PWD) modules_prepare
