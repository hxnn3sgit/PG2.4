class Graph {
	struct vertice {
		std::string name;
		std::string color;
		std::map<string, std::vector<std::string>>;
	};
	
	std::vector<vertice> vertices;
public:
	Graph() = default;
	void append_vertice(const std::string v_name);
};
