package application;

import java.util.ArrayList;

public class Process {
	private String name;
	private ArrayList<ST_Op> ops;
	private ArrayList<FG_Dep> deps;
}
class ST_Op{
	private String kind;
	private String name;
	private String arg;
}
class FG_Dep{
	private String name;
	private ArrayList<String> modes;
}