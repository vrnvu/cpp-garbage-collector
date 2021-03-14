enum ObjectType {
	INT,
	PAIR
};

struct Object {
	enum ObjectType type;
	bool marked;
	struct Object *next;

	union {
		int value;
		struct {
			struct Object *head;
			struct Object *tail;
		};
	};
};