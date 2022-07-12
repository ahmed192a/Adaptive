package application;

import java.util.HashMap;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;


public class Main extends Application {
	
    public static HashMap<String, String> Locations = new HashMap<String,String>();
    public static Node Tree;
    private static Stage primaryStage;
    private void setPrimaryStage(Stage stage) {Main.primaryStage = stage;}
    public static  Stage getPrimaryStage() {return Main.primaryStage;}
    
	@Override
	public void start(Stage primaryStage) {
		try {
	        setPrimaryStage(primaryStage);
			Parent root = FXMLLoader.load(getClass().getResource("Main.fxml")); 
			Scene scene = new Scene(root);
			scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
			primaryStage.setTitle("AUTOSAR Service Tool");
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
