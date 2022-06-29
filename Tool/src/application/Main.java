package application;
	
import java.io.IOException;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import javafx.scene.Parent;
import javafx.scene.Scene;

public class Main extends Application {
	
	// **Declare static Stage**  
	private static Stage primaryStage; 
	private void setPrimaryStage(Stage stage) {Main.primaryStage = stage;}
	static public Stage getPrimaryStage() {return Main.primaryStage;}
	
	@Override
	public void start(Stage primaryStage) throws IOException{
		Parent root = FXMLLoader.load(getClass().getResource("Main.fxml")); 
		Scene scene = new Scene(root);
		setPrimaryStage(primaryStage);
		scene.getStylesheets().add(getClass().getResource("application.css").toExternalForm());
		primaryStage.setTitle("AUTOSAR Generator Tool [ARA::EM]");
		primaryStage.setScene(scene);
		primaryStage.show();
	}
	
	public static void main(String[] args) {launch(args);}
}


