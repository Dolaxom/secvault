build: copy_all
	docker compose up --build
	make clean

build_swagger:
	cp -R ../../docs .
	docker compose up swagger
	make clean

build_api:
	cp -R ../backend/api .
	cp -R ../backend/proto .
	docker compose up --build api
	make clean

clean:
	rm -rf docs
	rm -rf api
	rm -rf proto

copy_all:
	cp -R ../backend/api .
	cp -R ../backend/proto .
	cp -R ../../docs .
