build:
	cp -R ../../docs .
	docker compose up --build
	make clean

build_swagger:
	cp -R ../../docs .
	docker compose up swagger
	make clean

clean:
	rm -rf docs
