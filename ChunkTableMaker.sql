CREATE DATABASE chunk;

USE chunk;


CREATE TABLE files (
	file_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	file_name VARCHAR(255) NOT NULL,
	file_length BIGINT UNSIGNED	NOT NULL,
	PRIMARY KEY (file_id),
	UNIQUE (file_name, file_length)
);


CREATE TABLE chunks (
	chunk_id INT UNSIGNED NOT NULL,
	file_id INT UNSIGNED NOT NULL,
	chunk_hash BINARY(32) NOT NULL,
	chunk_begin_pos BIGINT UNSIGNED NOT NULL,
	chunk_length BIGINT UNSIGNED NOT NULL,
	PRIMARY KEY (chunk_id, file_id),
	FOREIGN KEY (file_id) REFERENCES files(file_id) 
	ON DELETE CASCADE 
	ON UPDATE CASCADE
);