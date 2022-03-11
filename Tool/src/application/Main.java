package application;
	
import java.util.ArrayList;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;


public class Main extends Application {
	
	
    private static Stage primaryStage; // **Declare static Stage**    
    public static Node Tree;
    
    public static String Direc;

    public static String File;
    public static String Data;  

    public static ArrayList<String> sFile = new ArrayList<String>();
    public static ArrayList<String> sData = new ArrayList<String>();;

    public static ArrayList<String> pFile = new ArrayList<String>();;
    public static ArrayList<String> pData = new ArrayList<String>();; 

    private void setPrimaryStage(Stage stage) {
        Main.primaryStage = stage;
    }

    static public Stage getPrimaryStage() {
        return Main.primaryStage;
    }

	@Override
	public void start(Stage primaryStage) {
		try {
	        setPrimaryStage(primaryStage);
			Parent root = FXMLLoader.load(getClass().getResource("Main.fxml")); 
			Scene scene = new Scene(root);
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			primaryStage.setTitle("AUTOSAR Generator Tool");
			Image icon = new Image("icon.png");
			primaryStage.getIcons().add(icon);
			primaryStage.setResizable(true);
			primaryStage.setMinWidth(920);
			primaryStage.setMinHeight(640);
			primaryStage.setScene(scene);
			primaryStage.show();
	
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		launch(args);
	}
}
